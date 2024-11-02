#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

bool checkingTheBalanceOfBrackets(const char* string) {
    int balance = 0;
    bool balanceHasBeenChanged = false;
    int i = 0;
    while (string[i] != '\0') {
        if (balance < 0) {
            return false;
        }
        else if (string[i] == '(') {
            balance += 1;
            balanceHasBeenChanged = true;
        }
        else if (string[i] == ')') {
            balance -= 1;
            balanceHasBeenChanged = true;
        }
        ++i;
    }
    if (!balanceHasBeenChanged) {
        return true;
    }
    return balance == 0;
}

bool checkingUserInput(const char* string) {
    const char correctCharacters[] = "0123456789+-*/( )";
    int i = 0;

    if (NULL == string) {
        return false;
    }

    while (string[i] != '\0') {
        if (NULL == strchr(correctCharacters, string[i])) {
            return false;
        }
        ++i;
    }

    return true;
}

char* userInput(bool *errorCode) {
    char* inputString = (char*)calloc(1, sizeof(char));
    if (inputString == NULL) {
        printf("Ошибка выделения памяти");
        *errorCode = true;
        return NULL;
    }
    size_t bufferSize = 1;
    size_t lineLength = 0;

    while (true) {
        char oneCharacter = getchar();

        if (oneCharacter == '\n') {
            break;
        }

        if (lineLength + 1 >= bufferSize) {
            bufferSize *= 2;
            char* tmp = (char*)realloc(inputString, bufferSize * sizeof(char));
            if (tmp == NULL) {
                printf("Ошибка выделения памяти");
                *errorCode = true;
                return NULL;
            }
            inputString = tmp;
        }
        inputString[lineLength++] = oneCharacter;
    }

    inputString[lineLength] = '\0';
    if (checkingUserInput(inputString) && checkingTheBalanceOfBrackets(inputString)) {
        return inputString;
    }
    else if (!checkingUserInput(inputString)) {
        printf("Строка должна содержать только символы указанные выше, попробуйте ещё раз\n");
        free(inputString);
        userInput(errorCode);
    }
    else if (!checkingTheBalanceOfBrackets(inputString)) {
        printf("Не выполняется баланс скобок, попробуйте ещё раз\n");
        free(inputString);
        userInput(errorCode);
    }
}