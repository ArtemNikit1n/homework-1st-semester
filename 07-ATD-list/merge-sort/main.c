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
        printf("%s - %s\n", getValue(next(i, errorCode), errorCode).name, getValue(next(i, errorCode), errorCode).phone);
        if (*errorCode) {
            printf("Ошибка. Вывод ваших контактов остановлен.\n");
            return;
        }
    }
    printf("\n");
}

void readFromTheFile(List* records, const char* filename, bool* errorCode) {
    FILE* file = fopen(filename, "r");
    if (file == NULL || records == NULL) {
        *errorCode = true;
        return;
    }

    Position i = first(records, errorCode);
    int scanfResult = 2;
    while (scanfResult == 2) {
        char* name = calloc(1, sizeof(char) * MAX_NAME_LENGTH);
        char* phone = calloc(1, sizeof(char) * MAX_PHONE_LENGTH);
        scanfResult = fscanf(file, "%s - %s\n", name, phone);
        if (scanfResult != 2) {
            break;
        }

        NameAndPhone currentData = { .name = name, .phone = phone };
        add(records, i, currentData, errorCode);
        i = next(i, errorCode);
    }
    fclose(file);
}

void callTheFunction(int functionCode, bool* errorCode) {
    List* records = createList(errorCode);
    if (*errorCode == true) {
        printf("Ошибка выделения памяти");
        return;
    }
    readFromTheFile(records, "phoneDatabase.txt", errorCode);
    if (*errorCode) {
        deleteList(&records);
        printf("Ошибка при чтении из файла");
        return;
    }
    while (functionCode != 0) {
        if (functionCode == 1) {
            sortByMerging(records, next(first(records, errorCode), errorCode), NULL, phone, errorCode);
            if (*errorCode) {
                deleteList(&records);
                printf("Произошла ошибка, попробуйте позже\n");
                return;
            }
            printf("Номера телефонов были успешно отсортированы!\n");
        }
        if (functionCode == 2) {
            sortByMerging(records, next(first(records, errorCode), errorCode), NULL, name, errorCode);
            if (*errorCode) {
                deleteList(&records);
                printf("Произошла ошибка, попробуйте позже\n");
                return;
            }
            printf("Имена контактов были успешно отсортированы!\n");
        }
        if (functionCode == 3) {
            printf("Ваши контакты:\n");
            printList(records, errorCode);
        }
        functionCode = getTheFunctionCodeFromTheUser();
    }
    deleteList(&records);
}

int getTheFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 3 || functionCode < 0 || scanfReturns != 1) {
        printf("Номер команды введён некорректно, попробуйте ещё раз\n");
        printTheBackgroundInformation();
        while (getchar() != '\n');
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

    printTheBackgroundInformation();
    callTheFunction(getTheFunctionCodeFromTheUser(), &errorCode);

    return errorCode;
}