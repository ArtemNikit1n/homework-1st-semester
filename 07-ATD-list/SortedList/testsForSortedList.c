#include <stdbool.h>
#include <stdio.h>

#include "sortedList.h"

bool testSortTheList(bool *errorCode) {
    List* list = createList(errorCode);
    if (*errorCode) {
        return false;
    }
    add(list, 0, 123, errorCode);
    add(list, 1, 321, errorCode);
    add(list, 0, 456, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    sortTheList(list, 3, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    bool test1 = removeListElement(list, 2, errorCode) == 456 && removeListElement(list, 1, errorCode) == 321 && removeListElement(list, 0, errorCode) == 123;
    sortTheList(list, 0, errorCode);
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