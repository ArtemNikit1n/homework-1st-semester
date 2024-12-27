#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

#include "../Tree/tree.h"
#include "../Tree/testsForTree.h"
#include "dictionary.h"

void printTheBackgroundInformation() {
    printf(
        "0 � �����\n"
        "1 � �������� �������� � �������\n"
        "2 � ������� �������� �� �����\n"
        "3 � ��������� ������� ��������� ����� � �������\n"
        "4 - ������� �������� ���� � ��������� � ��� �������� �� �������\n\n"
    );
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char* getValueFromTheUser(bool* errorCode) {
    int buffer = 101;
    char* value = calloc(buffer, sizeof(char));
    if (value == NULL) {
        *errorCode = true;
        return NULL;
    }
    printf("������� ��������:\n");
    scanf("%101s", value);
    while (strlen(value) == buffer) {
        printf("������� ������� ������� ������, ���������� ��� ���\n");
        clearBuffer();
        scanf("%101s", value);
    }
    return value;
}

int getNumberFromTheUser(void) {
    int number = -1;
    int scanfReturns = scanf("%d", &number);
    while (scanfReturns != 1) {
        printf("����� ������������ ����, ���������� ��� ���:\n");
        clearBuffer();
        scanfReturns = scanf("%d", &number);
    }
    return number;
}

int getTheFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    printTheBackgroundInformation();
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 4 || functionCode < 0 || scanfReturns != 1) {
        printf("����� ������������ ����� �������, ���������� ��� ���:\n");
        printTheBackgroundInformation();
        clearBuffer();
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

void callTheFunction(int functionCode, bool* errorCode) {
    Node* root = NULL;
    while (functionCode != 0) {
        if (functionCode == 1) {
            printf("������� ����:\n");
            int key = getNumberFromTheUser();
            char* value = getValueFromTheUser(errorCode);
            if (*errorCode) {
                *errorCode = false;
                printf("������ ��������� ������, ���������� � ������ ���\n");
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }

            if (root == NULL) {
                root = createTree(key, value, errorCode);
                if (*errorCode) {
                    *errorCode = false;
                    free(value);
                    printf("������ ��������� ������, ���������� � ������ ���\n");
                    functionCode = getTheFunctionCodeFromTheUser();
                    continue;
                }
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }
            addNode(root, key, value, errorCode);
        }
        if (functionCode == 2) {
            printf("������� ����:\n");
            int theKeyForTheSearch = getNumberFromTheUser();
            char* theFoundString = searchByKey(root, theKeyForTheSearch);
            printf("%s\n", theFoundString);
        }
        if (functionCode == 3) {
            printf("������� ����:\n");
            int theKeyForTheSearch = getNumberFromTheUser();
            char* theFoundString = searchByKey(root, theKeyForTheSearch);
            if (theFoundString != NULL) {
                printf("���� ������\n");
            } else {
                printf("���� �� ������\n");
            }
        }
        if (functionCode == 4) {
            printf("������� ����:\n");
            int theKeyToDelete = getNumberFromTheUser();
            root = deleteNode(root, theKeyToDelete, errorCode);
            printf("���� ������� �����!\n");
        }
        functionCode = getTheFunctionCodeFromTheUser();
    }
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;

    runTheDictionaryTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    callTheFunction(getTheFunctionCodeFromTheUser(), &errorCode);
    return errorCode;
}