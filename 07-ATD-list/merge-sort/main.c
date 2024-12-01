#define _CRT_SECURE_NO_WARNINGS

#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 20

#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "mergeSort.h"
#include "../list/list.h"
#include "../list/testsForList.h"

typedef struct NamesAndPhones {
    List* phones;
    List* names;
} NamesAndPhones;

void printTheBackgroundInformation() {
    printf(
        "0 – выйти\n"
        "1 – отсортировать по номеру телефона\n"
        "2 – отсортировать по имени\n"
        "3 – распечатать данные из файла\n"
    );
}

void printList(const List* list, bool* errorCode) {
    for (Position i = first(list, errorCode); i != last(list, errorCode); i = next(i, errorCode)) {
        printf("%s ", getValue(next(i, errorCode), errorCode));
        if (*errorCode) {
            printf("Модуль списка сработал некорректно\n");
            return;
        }
    }
    printf("\n");
}

void readFromTheFile(NamesAndPhones* records, const char* filename, bool* errorCode) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        *errorCode = true;
        return;
    }

    List* names = createList(errorCode);
    Position i = first(names, errorCode);

    List* phones = createList(errorCode);
    Position j = first(phones, errorCode);

    if (*errorCode) {
        deleteList(&names);
        deleteList(&phones);
        return;
    }
    int scanfResult = 2;
    while (scanfResult == 2) {
        char* name = calloc(1, sizeof(char) * MAX_NAME_LENGTH);
        char* phone = calloc(1, sizeof(char) * MAX_PHONE_LENGTH);
        scanfResult = fscanf(file, "%s - %s\n", name, phone);
        if (scanfResult != 2) {
            break;
        }

        add(names, i, name, errorCode);
        i = next(i, errorCode);
        if (*errorCode) {
            deleteList(&names);
            deleteList(&phones);
            return;
        }

        add(phones, j, phone, errorCode);
        j = next(j, errorCode);
        if (*errorCode) {
            deleteList(&names);
            deleteList(&phones);
            return;
        }
    }
    records->names = names;
    records->phones = phones;
    fclose(file);
}

void callTheFunction(int functionCode, bool* errorCode) {
    NamesAndPhones* records = calloc(1, sizeof(NamesAndPhones));
    if (records == NULL) {
        *errorCode = true;
        free(records);
        printf("Ошибка выделения памяти");
        return;
    }
    readFromTheFile(records, "phoneDatabase.txt", errorCode);
    if (*errorCode) {
        deleteList(&records->phones);
        deleteList(&records->names);
        free(records);
        printf("Ошибка в чтении из файла памяти");
        return;
    }
    while (functionCode != 0) {
        if (functionCode == 1) {
            sortByMerging(records->phones, first(records->phones, errorCode), NULL, errorCode);
            if (*errorCode) {
                deleteList(&records->phones);
                deleteList(&records->names);
                printf("Произошла ошибка\n");
                return;
            }
            printf("Список был успешно отсортирован!\n");
        }
        if (functionCode == 2) {
            sortByMerging(records->names, first(records->names, errorCode), NULL, errorCode);
            if (*errorCode) {
                deleteList(&records->phones);
                deleteList(&records->names);
                printf("Произошла ошибка\n");
                return;
            }
            printf("Список был успешно отсортирован!\n");
        }
        if (functionCode == 3) {
            printf("Имена:\n");
            printList(records->names, errorCode);
            printf("Номера телефонов:\n");
            printList(records->phones, errorCode);
        }
        functionCode = getTheFunctionCodeFromTheUser();
    }
    deleteList(&records->phones);
    deleteList(&records->names);
    free(records);
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
        printf("Номер команды введён некорректно, попробуйте ещё раз\n");
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
    runMergeSortingTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    callTheFunction(getTheFunctionCodeFromTheUser(), &errorCode);

    return errorCode;
}