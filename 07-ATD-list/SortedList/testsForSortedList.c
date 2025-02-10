#include <stdbool.h>
#include <stdio.h>

#include "sortedList.h"

bool isListSorted(List* list, bool* errorCode) {
    if (listIsEmpty(list, errorCode)) {
        return true;
    }
    for (Position i = next(first(list), errorCode); i != last(list, errorCode); i = next(i, errorCode)) {
        Position j = next(i, errorCode);
        if (*errorCode) {
            return false;
        }
        if (getValue(i, errorCode) > getValue(j, errorCode)) {
            return false;
        }
    }
    return true;
}

bool testSortTheList(bool *errorCode) {
    List* list = createList(errorCode);
    if (*errorCode) {
        return false;
    }
    addItToSortedList(list, 6, errorCode);
    addItToSortedList(list, 5, errorCode);
    bool test1 = isListSorted(list, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    addItToSortedList(list, 3, errorCode);
    addItToSortedList(list, 1, errorCode);
    addItToSortedList(list, 8, errorCode);
    addItToSortedList(list, 7, errorCode);
    addItToSortedList(list, 2, errorCode);
    addItToSortedList(list, 4, errorCode);
    bool test2 = isListSorted(list, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }

    deleteFromSortedList(list, 1, errorCode);
    bool test3 = isListSorted(list, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    deleteFromSortedList(list, 8, errorCode);
    deleteFromSortedList(list, 4, errorCode);
    bool test4 = isListSorted(list, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    deleteFromSortedList(list, 6, errorCode);
    deleteFromSortedList(list, 2, errorCode);
    deleteFromSortedList(list, 2, errorCode);
    deleteFromSortedList(list, 3, errorCode);
    deleteFromSortedList(list, 5, errorCode);
    deleteFromSortedList(list, 7, errorCode);

    bool test5 = isListSorted(list, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }

    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    bool test6 = listIsEmpty(list, errorCode);
    deleteList(&list);
    return test1 && test2 && test3 && test4 && test5 && test6;
}

void runTheSortedListTests(bool* errorCode) {
    if (!testSortTheList(errorCode)) {
        printf("Тест testSortTheList не пройден\n");
        *errorCode = true;
    }
}