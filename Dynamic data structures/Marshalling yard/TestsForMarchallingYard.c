#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "marchallingYard.h"

void testTheMarshallingYard(bool *errorCode) {
    bool test1 = strcmp(infixToPostfix("2 + 2 * 2", errorCode), "2 2 2 * +") == 0;
    if (*errorCode) {
        printf("Функция сработала с ошибкой\n");
        return;
    }
    bool test2 = strcmp(infixToPostfix("(1 + 1) * 2", errorCode), "1 1 + 2 *") == 0;
    if (*errorCode) {
        printf("Функция сработала с ошибкой\n");
        return;
    }
    bool test3 = strcmp(infixToPostfix("(1 + 12312432) * 123 + (0 - 123)", errorCode), "1 12312432 + 123 * 0 123 - + ") == 0;
    if (*errorCode) {
        printf("Функция сработала с ошибкой\n");
        return;
    }
    bool test4 = infixToPostfix("(((())))", errorCode) == NULL;
    if (*errorCode) {
        printf("Функция сработала с ошибкой\n");
        return;
    }
    if (!(test1 && test2 && test3 && test4)) {
        *errorCode = true;
        return;
    }
}