#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "sortedList.h"
#include "../list/list.h"
#include "../merge-sort/testForMergeSort.h"
#include "../list/testsForlist.h"
#include "testsForSortedList.h"

void printTheBackgroundInformation() {
    printf(
        "0 – выйти\n"
        "1 – добавить значение в сортированный список\n"
        "2 – удалить значение из списка\n"
        "3 – распечатать список\n");
}

int getIntValueFromUser(void) {
    int value = -1;
    int scanfReturns = scanf("%d", &value);
    while (scanfReturns != 1) {
        printf("Число введено некорректно, попробуйте ещё раз\n");
        while (getchar() != '\n');
        scanfReturns = scanf("%d", &value);
    }
    return value;
}

void callTheFunction(int functionCode, bool* errorCode) {
    List* list = createList(errorCode);
    int listLength = 0;
    if (*errorCode) {
        deleteList(&list);
        return;
    }
    while (functionCode != 0) {
        if (functionCode == 1) {
            printf("Введите число, которое вы хотите добавить в список\n");
            addItToSortedList(list, getIntValueFromUser(), errorCode);

            if (*errorCode) {
                printf("При добавлении числа произошла ошибка\n");
                *errorCode = false;
            } else {
                ++listLength;
                printf("Число было успешно добавлено!\n");
            }
        }

        if (functionCode == 2) {
            if (listLength == 0) {
                printf("Список пуст\n");
                functionCode = getIntValueFromUser();
                while (functionCode > 3 || functionCode < 0) {
                    printf("Числа могут быть только от 1 до 3\n");
                    functionCode = getIntValueFromUser();
                }
                continue;
            }

            printf(
                "Введите позицию, которую вы хотите удалить из списка\n"
                "(От 1 до %d)\n", listLength);

            int position = getIntValueFromUser();
            while (position <= 0 || position > listLength) {
                printf("В вашем списке нет такой позиции. Попробуйте ещё раз\n");
                position = getIntValueFromUser();
            }
            deleteFromSortedList(list, position, errorCode);

            if (*errorCode) {
                printf("При удалении числа произошла ошибка\n");
                *errorCode = false;
            } else {
                printf("Число успешно удалено\n");
                --listLength;
            }
        }

        if (functionCode == 3) {
            if (listLength == 0) {
                printf("Список пуст\n");
            } else {
                printList(list, errorCode);
            }
        }

        functionCode = getIntValueFromUser();
        while (functionCode > 3 || functionCode < 0) {
            printf("Числа могут быть только от 1 до 3\n");
            functionCode = getIntValueFromUser();
        }
    }
    deleteList(&list);
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    runTheListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    runMergeSortingTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    runTheSortedListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    printTheBackgroundInformation();
    int functionCode = getIntValueFromUser();
    while (functionCode > 3 || functionCode < 0) {
        printf("Числа могут быть только от 1 до 3\n");
        functionCode = getIntValueFromUser();
    }
    callTheFunction(functionCode, &errorCode);

    return errorCode;
}