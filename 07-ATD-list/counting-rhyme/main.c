#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "../TheCyclicList/theCyclicList.h"
#include "../TheCyclicList/testsForList.h"

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getANumberFromTheUser(void) {
    int number = -1;
    int scanfReturns = scanf("%d", &number);
    while (scanfReturns != 1) {
        printf("������ �����, ���������� ��� ���\n");
        clearBuffer();
        scanfReturns = scanf("%d", &number);
    }
    clearBuffer();
    return number;
}

int calculateTheLastRemainingPosition(const int theNumberOfWars, int theDeadOfWar, bool* errorCode) {
    List* list = createList(errorCode);
    int j = 1;
    for (Position i = first(list, errorCode); j <= theNumberOfWars; i/* = next(i, errorCode)*/) {
        i = add(list, i, j, errorCode);
        ++j;
        if (*errorCode) {
            deleteList(&list);
            return -1;
        }
    }

    int theLastWarriorKilled = -1;
    while (!listIsEmpty(list, errorCode)) {
        theLastWarriorKilled = removeListElement(list, theDeadOfWar - 1, errorCode);
        if (*errorCode) {
            deleteList(&list);
            return -1;
        }
        theDeadOfWar = (theDeadOfWar + 2) % 41;
    }
    return theLastWarriorKilled;
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    runTheListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    printf("������� n (���������� ������):\n");
    int theNumberOfWars = 41;
    printf("������� ������� m-��. ������� m:\n");
    int theDeadOfWar = 3;
    int theSurvivor = calculateTheLastRemainingPosition(theNumberOfWars, theDeadOfWar, &errorCode);
    if (errorCode) {
        printf("��������� ������\n");
        return errorCode;
    }
    printf("%d (������� ��� ���� ������� ��������� � �����)\n", theSurvivor);
    return errorCode;
}