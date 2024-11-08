#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>

#include "workingWithAFile.h"
#include "testsWorkingWithAFile.h"

void outputOfReferenceInformation(void) {
    printf("\n------------------"
        "\nГлавное меню:"
        "\n0 - выйти"
        "\n1 - добавить запись (имя и телефон)"
        "\n2 - распечатать все имеющиеся записи"
        "\n3 - найти телефон по имени"
        "\n4 - найти имя по телефону"
        "\n5 - сохранить текущие данные в файл\n");
}

short userInput(bool *errorCode) {
    outputOfReferenceInformation();

    char *strCommandNumber = (char *)calloc(10, sizeof(char));
    char *endptrCommandNumber = NULL;
    short commandNumber = -1;

    assert(strCommandNumber != NULL);

    printf("\nВведите команду: ");
    scanf("%s", strCommandNumber);
    commandNumber = (short)strtol(strCommandNumber, &endptrCommandNumber, 10);

    if (commandNumber < 0 || commandNumber > 6 || *endptrCommandNumber != '\0') {
        printf("\nНекорректный номер команды, попробуйте ещё раз\n");
        free(strCommandNumber);
        userInput(errorCode);
    } else {
        free(strCommandNumber);
        return commandNumber;
    }
}

void callingTheFunction(struct NameAndPhoneNumber* records, short commandNumber, bool *errorCode) {
    if (commandNumber == 0) {
        printf("Выход из справочника...\n");
        return;
    }
    else if (commandNumber == 1) {
        printf("\nДобавление записи\n\n");
        addANewContact(records);
        commandNumber = userInput(errorCode);
        callingTheFunction(records, commandNumber, errorCode);
    }
    else if (commandNumber == 2) {
        printAllAvailableRecords(records);
        commandNumber = userInput(errorCode) ;
        callingTheFunction(records, commandNumber, errorCode);
    }
    else if (commandNumber == 3) {
        char *name = userInputForSearchByName();
        searchByName(records, name);
        commandNumber = userInput(errorCode);
        callingTheFunction(records, commandNumber, errorCode);
    }
    else if (commandNumber == 4) {
        char *phone = userInputForSearchByPhone();
        searchByPhone(records, phone);
        commandNumber = userInput(errorCode); 
        callingTheFunction(records, commandNumber, errorCode);
    }
    else if (commandNumber == 5) {
        saveToFile(records, "phoneDatabase.txt");
        commandNumber = userInput(errorCode);
        callingTheFunction(records, commandNumber, errorCode);
    }
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool errorCode = false;


    if (!testSearchByName) {
        printf("Тест testSearchByName не пройден");
        errorCode = true;
        return errorCode;
    }

    if (!testSearchByPhone) {
        printf("Тест testSearchByPhone не пройден");
        errorCode = true;
        return errorCode;
    }

    short commandNumber = userInput(&errorCode);
    struct NameAndPhoneNumber records = {
        .numberOfEntries = 0,
        .names = { { '\0' } },
        .phones = { { '\0' } }
    };

    readingFromAFile(&records, "phoneDatabase.txt");
    callingTheFunction(&records, commandNumber, &errorCode);
    while (errorCode) {
        callingTheFunction(&records, commandNumber, &errorCode);
    }

    return errorCode;
}