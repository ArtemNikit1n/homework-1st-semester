#include <stdbool.h>
#include <stdio.h>

#include "sortedList.h"

bool testSortTheList(bool *errorCode) {
    List* list = createList(errorCode);
    addItToSortedList(list, 123, errorCode);
    addItToSortedList(list, -23, errorCode);
    addItToSortedList(list, 0, errorCode);
    addItToSortedList(list, -33232, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    deleteFromSortedList(list, 1, errorCode);
    deleteFromSortedList(list, 3, errorCode);
    deleteFromSortedList(list, 2, errorCode);
    deleteFromSortedList(list, 1, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    bool test1 = listIsEmpty(list, errorCode);
    deleteList(&list);
    return test1;
}

void runTheSortedListTests(bool* errorCode) {
    if (!testSortTheList(errorCode)) {
        printf("���� testSortTheList �� �������\n");
        if (*errorCode) {
            printf("������ � ������ ������\n");
        }
        *errorCode = true;
    }
}