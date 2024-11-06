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
        printf("Ошибка ввода, попробуйте ещё раз\n");
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

bool testForCalculateTheLastRemainingPosition(bool *errorCode) {
    bool test1 = 31 == calculateTheLastRemainingPosition(41, 3, errorCode);
    bool test2 = 1 == calculateTheLastRemainingPosition(8, 2, errorCode);
    bool test3 = 7 == calculateTheLastRemainingPosition(10, 11, errorCode);
    return test1 && test2 && test3;
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    if (!testForCalculateTheLastRemainingPosition(&errorCode)) {
        printf("Тест calculateTheLastRemainingPosition не пройден\n");
        if (errorCode) {
            printf("Произошла ошибка или нарушен инвариан\n");
        }
        return errorCode;
    }
    runTheListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    printf("Введите n (количество войнов):\n");
    int theNumberOfWars = getANumberFromTheUser();
    printf("Убивают каждого m-го. Введите m:\n");
    int theDeadOfWar = getANumberFromTheUser();
    while (theDeadOfWar < 0 || theNumberOfWars <= 0 ) {
        printf("Так не бывает, попробуйте ещё раз\n");
        printf("Введите n (количество войнов):\n");
        theNumberOfWars = getANumberFromTheUser();
        printf("Убивают каждого m-го. Введите m:\n");
        theDeadOfWar = getANumberFromTheUser();
    }
    if (theDeadOfWar == 1) {
        printf("Все умрут:(\n");
        return errorCode;
    }
    if (theDeadOfWar == 0) {
        printf("Никто не умрёт:)\n");
        return errorCode;
    }
    int theSurvivor = calculateTheLastRemainingPosition(theNumberOfWars, theDeadOfWar, &errorCode);
    if (errorCode) {
        printf("Произошла ошибка\n");
        return errorCode;
    }
    printf("%d (Человек под этим номером останется в живых)\n", theSurvivor);
    return errorCode;
}