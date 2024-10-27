﻿#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "userInput.h"
#include "testsForUserInput.h"
#include "testsForStack.h"
#include "testForQueue.h"

void runningTests(bool* errorCode) {
    if (!testForEnqueueAndDequeue()) {
        printf("Тест testForEnqueueAndDequeue() не пройден\n");
        *errorCode = true;
    }
    if (!testCheckingTheBalanceOfBrackets()) {
        printf("Тест testCheckingTheBalanceOfBrackets() не пройден\n");
        *errorCode = true;
    }
    if (!testCheckingUserInput()) {
        printf("Тест testCheckingUserInput не пройден\n");
        *errorCode = true;
    }
    if (!testCreateStack()) {
        printf("Тест testCreateStack не пройден\n");
        *errorCode = true;
    }
    if (!testDeleteStack()) {
        printf("Тест testDeleteStack не пройден\n");
        *errorCode = true;
    }
    if (!testIsEmpty()) {
        printf("Тест testIsEmpty не пройден\n");
        *errorCode = true;
    }
    if (!testPushAndStackSize()) {
        printf("Тест testPushAndStackSize не пройден\n");
        *errorCode = true;
    }
    if (!testPop()) {
        printf("Тест testPop не пройден\n");
        *errorCode = true;
    }
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool errorCode = false;

    runningTests(&errorCode);

    printf("Введите выражение в постфиксной форме:\n"
        "Разрешённые символы: {0123456789+-*/( )}\n");

    char* infixForm = userInput();

    return errorCode;
}