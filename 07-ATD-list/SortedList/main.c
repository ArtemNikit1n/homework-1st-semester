#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "sortedList.h"
#include "../list/list.h"
#include "../list/testsForlist.h"
#include "testsForSortedList.h"

void printTheBackgroundInformation() {
    printf(
        "0 � �����\n"
        "1 � �������� �������� � ������������� ������\n"
        "2 � ������� �������� �� ������\n"
        "3 � ����������� ������\n");
}

void callTheFunction(int functionCode, bool* errorCode) {
    List* list = createList(errorCode);
    int listLength = 0;
    if (*errorCode) {
        deleteList(&list);
        return;
    }
    while (functionCode != 0) {
        if (functionCode == 1) {
            addItToTheSortedList(list, errorCode);
            if (*errorCode) {
                printf("��� ���������� ����� ��������� ������\n");
                *errorCode = false;
            } else {
                ++listLength;
                printf("����� ���� ������� ���������!\n");
            }
            sortTheList(list, listLength, errorCode);
            if (*errorCode) {
                printf("��� ���������� ��������� ������\n");
                *errorCode = false;
            }
        }
        if (functionCode == 2) {
            if (listLength == 0) {
                printf("������ ����\n");
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }
            removeANumberFromTheSortedList(list, listLength, errorCode);
            if (*errorCode) {
                printf("��� �������� ����� ��������� ������\n");
                *errorCode = false;
            } else {
                printf("����� ������� �������\n");
                --listLength;
            }
        }
        if (functionCode == 3) {
            printList(list, listLength, errorCode);
        }
        functionCode = getTheFunctionCodeFromTheUser();
    }
    deleteList(&list);
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getTheFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    printTheBackgroundInformation();
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 3 || functionCode < 0 || scanfReturns != 1) {
        printf("������� ������� �����������, ���������� ��� ���\n");
        printTheBackgroundInformation();
        clearBuffer();
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    runTheListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    runTheSortedListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    callTheFunction(getTheFunctionCodeFromTheUser(), &errorCode);

    return errorCode;
}