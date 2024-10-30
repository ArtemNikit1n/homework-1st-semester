#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "marchallingYard.h"

bool testTheMarshallingYard(bool *errorCode) {
    bool test1 = strcmp(infixToPostfix("2 + 2 * 2", errorCode), "2 2 2 * + ") == 0;
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        return false;
    }
    bool test2 = strcmp(infixToPostfix("(1 + 1) * 2", errorCode), "1 1 + 2 * ") == 0;
    if (*errorCode) {
        printf("������� ��������� � �������\n");
        return false;
    }
    return test1 && test2;
}