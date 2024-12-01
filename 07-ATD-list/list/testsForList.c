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
    NameAndPhone testStruct1 = { .name = "Artem", .phone = "89123599486" };
    NameAndPhone testStruct2 = { .name = '\0', .phone = '\0'};
    NameAndPhone testStruct3 = { .name = "Мишка", .phone = "Мёд" };

    add(list, first(list, errorCode), testStruct1, errorCode);
    add(list, next(first(list, errorCode), errorCode), testStruct2, errorCode);
    add(list, next(next(first(list, errorCode), errorCode), errorCode), testStruct3, errorCode);
    if (*errorCode) {
        deleteList(&list);
        return false;
    }

    bool test1 = removeListElement(list, next(first(list, errorCode), errorCode), errorCode).phone == testStruct2.phone;
    bool test2 = strcmp(getValue(next(first(list, errorCode), errorCode), errorCode).phone, testStruct1.phone) == 0;
    bool test3 = strcmp(removeListElement(list, first(list, errorCode), errorCode).name, testStruct1.name) == 0;
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