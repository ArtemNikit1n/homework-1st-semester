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

    add(list, first(list, errorCode), 123, errorCode);
    add(list, next(first(list, errorCode), errorCode), 0, errorCode);
    add(list, next(next(first(list, errorCode), errorCode), errorCode), -123, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }

    bool test1 = removeListElement(list, next(first(list, errorCode), errorCode), errorCode) == 0;
    bool test2 = getValue(next(first(list, errorCode), errorCode), errorCode) == 123;
    bool test3 = removeListElement(list, first(list, errorCode), errorCode) == 123;
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

void runTheListTests(bool* errorCode) {
    if (!testListIsEmptyAndCreateList(errorCode)) {
        printf("Тест testListIsEmptyAndCreateList не пройден\n");
        if (*errorCode) {
            printf("Ошибка в работе модуля\n");
        }
        *errorCode = true;
    }
    if (!testAddAndRemove(errorCode)) {
        printf("Тест testAddAndRemove не пройден\n");
        if (*errorCode) {
            printf("Ошибка в работе модуля\n");
        }
        *errorCode = true;
    }
}