#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../merge-sort/mergeSort.h"
#include "../list/list.h"

void printList(const List* list, bool* errorCode) {
    for (Position i = first(list, errorCode); i != last(list, errorCode); i = next(i, errorCode)) {
        printf("%d ", getValue(next(i, errorCode), errorCode));
        if (*errorCode) {
            printf("Ошибка. Невозможно вывести список.\n");
            return;
        }
    }
    printf("\n");
}

void addItToSortedList(List* list, int valueToAdd, bool* errorCode) {
    add(list, last(list, errorCode), valueToAdd, errorCode);
    sortByMerging(list, next(first(list, errorCode), errorCode), NULL, errorCode);
}

void deleteFromSortedList(List* list, int position, bool* errorCode) {
    int j = 1;
    Position i = first(list, errorCode);
    while (j < position) {
        i = next(i, errorCode);
        ++j;
    }
    removeListElement(list, i, errorCode);
}