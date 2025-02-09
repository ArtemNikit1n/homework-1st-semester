#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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
    add(list, first(list, errorCode), "123qwe", errorCode);
    add(list, next(first(list, errorCode), errorCode), "456aasd", errorCode);
    add(list, next(next(first(list, errorCode), errorCode), errorCode), '\0', errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }
    bool test1 = strcmp(getValue(next(next(first(list, errorCode), errorCode), errorCode), errorCode), "456aasd") == 0;
    removeListElement(list, next(next(first(list, errorCode), errorCode), errorCode), errorCode);
    bool test2 = strcmp(getValue(next(first(list, errorCode), errorCode), errorCode), "123qwe") == 0;
    removeListElement(list, first(list, errorCode), errorCode);
    bool test3 = getValue(first(list, errorCode), errorCode) == '\0';
    removeListElement(list, first(list, errorCode), errorCode);
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
        if (*errorCode) {
            printf("Ошибка в работе модуля\n");
        }
        *errorCode = true;
        return false;
    }
    if (!testAddAndRemove(errorCode)) {
        printf("Тест testAddAndRemove не пройден\n");
        if (*errorCode) {
            printf("Ошибка в работе модуля\n");
        }
        *errorCode = true;
        return false;
    }
}