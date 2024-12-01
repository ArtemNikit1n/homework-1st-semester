#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../list/list.h"
#include "mergeSort.h"

bool checkTheLexicographicOrder(List* list, SortingCriteria criteria, bool* errorCode) {
    for (Position i = next(first(list, errorCode), errorCode); i != last(list, errorCode); i = next(i, errorCode)) {
        Position j = next(i, errorCode);

        char* iValue = NULL;
        char* jValue = NULL;
        if (criteria == name) {
            iValue = getValue(i, errorCode).name;
            jValue = getValue(j, errorCode).name;
        }
        if (criteria == phone) {
            iValue = getValue(i, errorCode).phone;
            jValue = getValue(j, errorCode).phone;
        }
        int strcmpResult = -2;
        if (iValue == '\0' || jValue == '\0') {
            if (iValue == '\0' && jValue != '\0') {
                strcmpResult = -1;
            }
            if (iValue != '\0' && jValue == '\0') {
                strcmpResult = 1;
            }
            if (iValue == '\0' && jValue == '\0') {
                strcmpResult = 0;
            }
        }
        else {
            strcmpResult = strcmp(iValue, jValue);
        }
        if (strcmpResult > 0) {
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
    NameAndPhone testStruct = { .name = "Artem", .phone = "89123599486" };
    add(testList, first(testList, errorCode), testStruct, errorCode);
    testStruct.name = "Nikitka";
    testStruct.phone = "89123219486";
    add(testList, first(testList, errorCode), testStruct, errorCode);
    testStruct.name = '\0';
    testStruct.phone = "-023-12-";
    add(testList, first(testList, errorCode), testStruct, errorCode);
    testStruct.name = "Pashka";
    testStruct.phone = '\0';
    add(testList, first(testList, errorCode), testStruct, errorCode);

    sortByMerging(testList, next(first(testList, errorCode), errorCode), NULL, phone, errorCode);
    bool test1 = checkTheLexicographicOrder(testList, phone, errorCode);
    sortByMerging(testList, next(first(testList, errorCode), errorCode), NULL, name, errorCode);
    bool test2 = checkTheLexicographicOrder(testList, name, errorCode);
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