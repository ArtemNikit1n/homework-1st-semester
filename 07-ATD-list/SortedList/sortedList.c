#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../list/list.h"

void swap(int* first, int* second) {
    if (*first == *second) {
        return;
    }
    *first ^= *second;
    *second ^= *first;
    *first ^= *second;
}

void sortByInsertionSort(int* array, int start, int stop) {
    for (int i = start + 1; i <= stop; ++i) {
        int indexSave = i;
        while (array[i] < array[i - 1] && start < i) {
            swap(&array[i], &array[i - 1]);
            --i;
        }
        i = indexSave;
    }
}

void sortTheList(List* list, int listLength, bool* errorCode) {
    int* arrayForSorting = calloc(listLength, sizeof(int));
    if (NULL == arrayForSorting) {
        *errorCode = true;
        return;
    }
    for (int i = 0; i < listLength; ++i) {
        int element = removeListElement(list, 0, errorCode);
        arrayForSorting[i] = element;
        add(list, listLength - 1, element, errorCode);
        if (*errorCode) {
            return;
        }
    }
    sortByInsertionSort(arrayForSorting, 0, listLength - 1);
    for (int i = listLength - 1; i >= 0; --i) {
        removeListElement(list, i, errorCode);
        add(list, i, arrayForSorting[i], errorCode);
        if (*errorCode) {
            return;
        }
    }
}

void printList(List* list, int listLength, bool *errorCode) {
    if (listLength == 0) {
        printf("������ ����\n");
        return;
    }
    printf("������������� ������:\n");
    for (int i = 0; i < listLength; ++i) {
        int element = removeListElement(list, 0, errorCode);
        printf("%d ", element);
        add(list, listLength - 1, element, errorCode);
        if (*errorCode) {
            printf("��������� ������\n");
            return;
        }
    }
    printf("\n");
}

void addItToTheSortedList(List* list, bool* errorCode) {
    int value = -1;
    printf("������� �����, ������� �� ������ �������� � ������\n");
    int scanfReturns = scanf("%d", &value);
    while (scanfReturns != 1) {
        printf("����� ������� �����������, ���������� ��� ���\n");
        int c = 0;
        while ((c = getchar()) != '\n' && c != EOF);
        scanfReturns = scanf("%d", &value);
    }
    add(list, 0, value, errorCode);
}

void removeANumberFromTheSortedList(List* list, int listLength, bool* errorCode) {
    int position = -1;
    printf(
        "������� �������, ������� �� ������ ������� �� ������\n"
        "(�� 1 �� %d)\n", listLength);
    int scanfReturns = scanf("%d", &position);
    while (scanfReturns != 1 || position <= 0 || position > listLength) {
        printf("����� ������� �����������, ���������� ��� ���\n");
        int c = 0;
        while ((c = getchar()) != '\n' && c != EOF);
        scanfReturns = scanf("%d", &position);
    }
    removeListElement(list, position - 1, errorCode);
}