#include <stdbool.h>
#include <stdio.h>

#include "../list/list.h"

bool testListIsEmptyAndCreateList(bool* errorCode) {
    List* list = createList(errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    bool test = listIsEmpty(list, errorCode);
    deleteList(&list);
    return test;
}

bool testAddAndRemove(bool* errorCode) {
    List* list = createList(errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    add(list, first(list), 1, errorCode);
    add(list, next(first(list), errorCode), 2, errorCode);
    add(list, next(next(first(list), errorCode), errorCode), 3, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }

    bool test1 = removeListElement(list, next(first(list), errorCode), errorCode) == 2;
    bool test2 = getValue(next(first(list), errorCode), errorCode) == 1;
    bool test3 = removeListElement(list, first(list), errorCode) == 1;
    removeListElement(list, first(list), errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    bool test4 = listIsEmpty(list, errorCode);
    deleteList(&list);
    if (*errorCode) {
        return false;
    }
    return test1 && test2 && test3 && test4;
}

bool runTheListTests(bool* errorCode) {
    if (!testListIsEmptyAndCreateList(errorCode)) {
        printf("Тест testListIsEmptyAndCreateList не пройден\n");
        *errorCode = true;
        return false;
    }
    if (!testAddAndRemove(errorCode)) {
        printf("Тест testAddAndRemove не пройден\n");
        *errorCode = true;
        return false;
    }
}