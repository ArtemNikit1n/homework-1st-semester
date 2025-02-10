#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "sortedList.h"
#include "../list/list.h"
#include "../list/testsForlist.h"
#include "testsForSortedList.h"

void printTheBackgroundInformation(void) {
    printf(
        "0 Ц выйти\n"
        "1 Ц добавить значение в сортированный список\n"
        "2 Ц удалить значение из списка\n"
        "3 Ц распечатать список\n");
}

int getIntValueFromUser(void) {
    int value = -1;
    int scanfReturns = scanf("%d", &value);
    while (scanfReturns != 1) {
        printf("„исло введено некорректно, попробуйте ещЄ раз\n");
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
            printf("¬ведите число, которое вы хотите добавить в список\n");
            addItToSortedList(list, getIntValueFromUser(), errorCode);

            if (*errorCode) {
                printf("ѕри добавлении числа произошла ошибка\n");
                *errorCode = false;
            } else {
                ++listLength;
                printf("„исло было успешно добавлено!\n");
            }
        }

        if (functionCode == 2) {
            if (listLength == 0) {
                printf("—писок пуст\n");
                functionCode = getIntValueFromUser();
                while (functionCode > 3 || functionCode < 0) {
                    printf("„исла могут быть только от 1 до 3\n");
                    functionCode = getIntValueFromUser();
                }
                continue;
            }

            printf("¬ведите значение, которое вы хотите удалить из списка\n");

            int valueToDelete = getIntValueFromUser();
            deleteFromSortedList(list, valueToDelete, errorCode);

            if (*errorCode) {
                printf("ѕри удалении значени€ произошла ошибка\n");
                *errorCode = false;
            } else {
                printf("«начение успешно удалено\n");
                --listLength;
            }
        }

        if (functionCode == 3) {
            if (listLength == 0) {
                printf("—писок пуст\n");
            } else {
                printList(list, errorCode);
            }
        }

        functionCode = getIntValueFromUser();
        while (functionCode > 3 || functionCode < 0) {
            printf("„исла могут быть только от 1 до 3\n");
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
    runTheSortedListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    printTheBackgroundInformation();
    int functionCode = getIntValueFromUser();
    while (functionCode > 3 || functionCode < 0) {
        printf("„исла могут быть только от 1 до 3\n");
        functionCode = getIntValueFromUser();
    }
    callTheFunction(functionCode, &errorCode);

    return errorCode;
}