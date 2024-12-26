#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "marchallingYard.h"
#include "userInput.h"
#include "TestsForMarchallingYard.h"
#include "testsForQueue.h"
#include "../stack/testsForStack.h"

void runTests(bool* errorCode) {
    runStackTest(&errorCode);
    if (*errorCode) {
        return errorCode;
    }
    testForEnqueueAndDequeue(errorCode);
    if (*errorCode) {
        printf("Тест enqueueAndDequeue не пройден\n");
        *errorCode = true;
        return;
    }
    testTheMarshallingYard(errorCode);
    if (*errorCode) {
        printf("Тест marshallingYard не пройден\n");
        return;
    }
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool errorCode = false;

    runTests(&errorCode);

    printf("Введите выражение в инфиксной форме:\n"
        "Разрешённые символы: {0123456789+-*/( )}\n");

    char* infixForm = userInput(&errorCode);
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
    printf("Ваше выражение в постфиксной форме:\n");

    printf("%s", postfixForm);
    return errorCode;
 }