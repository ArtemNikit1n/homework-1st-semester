#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "marchallingYard.h"
#include "userInput.h"
#include "TestsForMarchallingYard.h"
#include "testsForUserInput.h"
#include "testsForQueue.h"
#include "../stack/testsForStack.h"

void runTests(bool* errorCode) {
    if (!testTheMarshallingYard(errorCode)) {
        printf("Тест testTheMarshallingYard() не пройден\n");
        *errorCode = true;
        return;
    }
    if (!testForEnqueueAndDequeue(errorCode)) {
        printf("Тест testForEnqueueAndDequeue() не пройден\n");
        *errorCode = true;
        return;
    }
    if (!testCheckingTheBalanceOfBrackets()) {
        printf("Тест testCheckingTheBalanceOfBrackets() не пройден\n");
        *errorCode = true;
        return;
    }
    if (!testCheckingUserInput()) {
        printf("Тест testCheckingUserInput не пройден\n");
        *errorCode = true;
        return;
    }
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool errorCode = false;

    runTests(&errorCode);
    runStackTest(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    printf("Введите выражение в постфиксной форме:\n"
        "Разрешённые символы: {0123456789+-*/( )}\n");

    char* infixForm = userInput();
    if (errorCode) {
        return errorCode;
    }
    char* postfixForm = infixToPostfix(infixForm, &errorCode);
    if (NULL == postfixForm) {
        printf("Вы ввели пустую строку или выражение состоящее из скобок!\n");
        return errorCode;
    }
    if (errorCode) {
        printf("Программа завершена с ошибкой\n");
        return errorCode;
    }
    printf("%s", postfixForm);
    return errorCode;
 }