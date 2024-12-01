#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../list/list.h"
#include "mergeSort.h"

bool isListSorted(List* list, bool* errorCode) {
    for (Position i = next(first(list, errorCode), errorCode); i != last(list, errorCode); i = next(i, errorCode)) {
        Position j = next(i, errorCode);
        if (getValue(i, errorCode) - getValue(i, errorCode) > 0) {
            return false;
        }
        if (*errorCode) {
            return false;
        }
    }
    return true;
}

bool testSortByMerging(bool* errorCode) {
    List* testList = createList(errorCode);
    add(testList, first(testList, errorCode), 123, errorCode);
    add(testList, first(testList, errorCode), 321, errorCode);
    add(testList, first(testList, errorCode), 0, errorCode);
    add(testList, first(testList, errorCode), -565465, errorCode);

    sortByMerging(testList, first(testList, errorCode), NULL, errorCode);
    bool test1 = isListSorted(testList, errorCode);
    deleteList(&testList);
    return test1;
}

void runMergeSortingTests(bool* errorCode) {
    if (!testSortByMerging(errorCode)) {
        printf("Тест testSortByMerging не пройден\n");
        if (*errorCode) {
            printf("Ошибка в работе модуля\n");
        }
        *errorCode = true;
    }
}