#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "../Tree/tree.h"

void printTheBackgroundInformation() {
    printf(
        "0 � �����\n"
        "1 � �������� �������� � �������\n"
        "2 � ������� �������� �� �����\n"
        "3 � ��������� ������� ��������� ����� � �������\n"
        "4 � ��������� ������� ��������� ����� � �������\n"
        "5 - ������� �������� ���� � ��������� � ��� �������� �� �������\n\n"
    );
}

void callTheFunction(int functionCode, bool* errorCode) {
    while (functionCode != 0) {
        if (functionCode == 1) {
            printf("�� ������\n");
        }
        if (functionCode == 2) {
            printf("�� ������\n");
        }
        if (functionCode == 3) {
            printf("�� ������\n");
        }
        functionCode = getTheFunctionCodeFromTheUser();
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getTheFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    printTheBackgroundInformation();
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 5 || functionCode < 0 || scanfReturns != 1) {
        printf("����� ������������ ����� �������, ���������� ��� ���:\n");
        printTheBackgroundInformation();
        clearBuffer();
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;

    runTheTreeTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    callTheFunction(getTheFunctionCodeFromTheUser(), &errorCode);
    return errorCode;
}