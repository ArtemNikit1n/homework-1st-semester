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
    for (Position i = first(list, errorCode); j <= theNumberOfWars; i) {
        i = add(list, i, j, errorCode);
        ++j;
        if (*errorCode) {
            deleteList(&list);
            return -1;
        }
    }
    int survivor = -1;
    Position i = last(list, errorCode);
    while (!listIsEmpty(list, errorCode)) {
        int j = 1;
        while (j < theDeadOfWar) {
            i = next(i, errorCode);
            ++j;
        }
        survivor = removeListElement(list, i, errorCode);
        if (*errorCode) {
            deleteList(&list);
            return -1;
        }
    }
    deleteList(&list);
    return survivor;
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    runTheListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    printf("������� n (���������� ������):\n");
    int theNumberOfWars = getANumberFromTheUser();
    printf("������� ������� m-��. ������� m:\n");
    int theDeadOfWar = getANumberFromTheUser();
    while (theDeadOfWar <= 0 || theNumberOfWars <= 0) {
        printf("��� �� ������, ���������� ��� ���\n");
        printf("������� n (���������� ������):\n");
        theNumberOfWars = getANumberFromTheUser();
        printf("������� ������� m-��. ������� m:\n");
        theDeadOfWar = getANumberFromTheUser();
    }
    if (theDeadOfWar == 1) {
        printf("��� �����:(\n");
        return errorCode;
    }
    if (theDeadOfWar == 0) {
        printf("����� �� ����:)\n");
        return errorCode;
    }
    int theSurvivor = calculateTheLastRemainingPosition(theNumberOfWars, theDeadOfWar, &errorCode);
    if (errorCode) {
        printf("��������� ������\n");
        return errorCode;
    }
    printf("%d (������� ��� ���� ������� ��������� � �����)\n", theSurvivor);
    return errorCode;
}