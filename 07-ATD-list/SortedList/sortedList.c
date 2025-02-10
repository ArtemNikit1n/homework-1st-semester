#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../list/list.h"

void insertLastElement(List* list, Position sortedEnd, bool* errorCode) {
    if (first(list) == sortedEnd) {
        return;
    }

    Position unsortedElement = next(sortedEnd, errorCode);
    Value valueToInsert = getValue(unsortedElement, errorCode);
    if (*errorCode) {
        return;
    }

    Position insertPosition = first(list);
    while (insertPosition != unsortedElement) {
        Value currentValue = getValue(next(insertPosition, errorCode), errorCode);
        if (currentValue > valueToInsert) {
            removeListElement(list, sortedEnd, errorCode);
            if (*errorCode) {
                return;
            }
            add(list, insertPosition, valueToInsert, errorCode);
            return;
        }
        insertPosition = next(insertPosition, errorCode);
        if (*errorCode) {
            return;
        }
    }
}

void printList(const List* list, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return;
    }
    if (errorCode == NULL) {
        return;
    }
    for (Position i = first(list); i != last(list, errorCode); i = next(i, errorCode)) {
        printf("%d ", getValue(next(i, errorCode), errorCode));
        if (*errorCode) {
            printf("Ошибка. Невозможно вывести список.\n");
            return;
        }
    }
    printf("\n");
}

void addItToSortedList(List* list, int valueToAdd, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return;
    }
    if (errorCode == NULL) {
        return;
    }
    Position penultimateElementInList = last(list, errorCode);
    if (*errorCode) {
        return;
    }
    add(list, penultimateElementInList, valueToAdd, errorCode);
    if (*errorCode) {
        return;
    }
    insertLastElement(list, penultimateElementInList, errorCode);
}

void deleteFromSortedList(List* list, int valueToDelete, bool* errorCode) {
    if (list == NULL) {
        *errorCode = true;
        return;
    }
    if (errorCode == NULL) {
        return;
    }
    for (Position i = first(list); i != last(list, errorCode); i = next(i, errorCode)) {
        if (valueToDelete == getValue(next(i, errorCode), errorCode)) {
            removeListElement(list, i, errorCode);
            return;
        }
        if (*errorCode) {
            return;
        }
    }
}