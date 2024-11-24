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
        "0 – Выход\n"
        "1 – Добавить значение в словарь\n"
        "2 – Вывести значение по ключу\n"
        "3 – Проверить наличие заданного ключа в словаре\n"
        "4 - Удалить заданный ключ и связанное с ним значение из словаря\n\n"
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
    printf("Введите значение:\n");
    scanf("%101s", value);
    while (strlen(value) == buffer) {
        printf("Введена слишком длинная строка, попробуйте ещё раз\n");
        clearBuffer();
        scanf("%101s", value);
    }
    return value;
}

int getNumberFromTheUser(void) {
    int number = -1;
    int scanfReturns = scanf("%d", &number);
    while (scanfReturns != 1) {
        printf("Введён некорректный ключ, попробуйте ещё раз:\n");
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
        printf("Введён некорректный номер команды, попробуйте ещё раз:\n");
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
            printf("Введите ключ:\n");
            int key = getNumberFromTheUser();
            char* value = getValueFromTheUser(errorCode);
            if (*errorCode) {
                *errorCode = false;
                printf("Ошибка выделения памяти, попробуйте в другой раз\n");
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }

            if (root == NULL) {
                NodeValue rootValue = createNodeValue(key, value);
                root = createNode(rootValue, errorCode);
                if (*errorCode) {
                    *errorCode = false;
                    free(value);
                    printf("Ошибка выделения памяти, попробуйте в другой раз\n");
                    functionCode = getTheFunctionCodeFromTheUser();
                    continue;
                }
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }
            addToTheDictionary(root, key, value, errorCode);
        }
        if (functionCode == 2) {
            printf("Введите ключ:\n");
            int theKeyForTheSearch = getNumberFromTheUser();
            char* theFoundString = findValueByTheKey(root, theKeyForTheSearch, errorCode);
            if (*errorCode) {
                *errorCode = false;
                printf("Ошибка поиска, попробуйте в другой раз\n");
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }
            printf("%s\n", theFoundString);
        }
        if (functionCode == 3) {
            printf("Введите ключ:\n");
            int theKeyForTheSearch = getNumberFromTheUser();
            char* theFoundString = findValueByTheKey(root, theKeyForTheSearch, errorCode);
            if (*errorCode) {
                *errorCode = false;
                printf("Ошибка поиска, попробуйте в другой раз\n");
                functionCode = getTheFunctionCodeFromTheUser();
                continue;
            }
            if (theFoundString != NULL) {
                printf("Ключ найден\n");
            } else {
                printf("Ключ не найден\n");
            }
        }
        if (functionCode == 4) {
            printf("Введите ключ:\n");
            int theKeyToDelete = getNumberFromTheUser();
            root = deleteByKey(root, theKeyToDelete, errorCode);
        }
        functionCode = getTheFunctionCodeFromTheUser();
    }
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;

    runTheTreeTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    runTheDictionaryTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    callTheFunction(getTheFunctionCodeFromTheUser(), &errorCode);
    return errorCode;
}