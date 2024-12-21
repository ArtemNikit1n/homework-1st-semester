#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>

#include "workingWithAFile.h"
#include "testsWorkingWithAFile.h"

void outputOfReferenceInformation(void) {
    printf("\n------------------"
        "\n������� ����:"
        "\n0 - �����"
        "\n1 - �������� ������ (��� � �������)"
        "\n2 - ����������� ��� ��������� ������"
        "\n3 - ����� ������� �� �����"
        "\n4 - ����� ��� �� ��������"
        "\n5 - ��������� ������� ������ � ����\n");
}

short userInput(bool *errorCode) {
    outputOfReferenceInformation();

    char *strCommandNumber = (char *)calloc(10, sizeof(char));
    char *endptrCommandNumber = NULL;
    short commandNumber = -1;

    assert(strCommandNumber != NULL);

    printf("\n������� �������: ");
    scanf("%s", strCommandNumber);
    commandNumber = (short)strtol(strCommandNumber, &endptrCommandNumber, 10);

    if (feof(stdin)) {
        return -1;
    }
    if (commandNumber < 0 || commandNumber > 6 || *endptrCommandNumber != '\0') {
        printf("\n������������ ����� �������, ���������� ��� ���\n");
        free(strCommandNumber);
        userInput(errorCode);
    } else {
        free(strCommandNumber);
        return commandNumber;
    }
}

void callingTheFunction(struct NameAndPhoneNumber* records, short commandNumber, bool *errorCode) {
    if (commandNumber == 0) {
        printf("����� �� �����������...\n");
        return;
    }
    else if (commandNumber == 1) {
        printf("\n���������� ������\n\n");
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
        printf("���� testSearchByName �� �������");
        errorCode = true;
        return errorCode;
    }

    if (!testSearchByPhone) {
        printf("���� testSearchByPhone �� �������");
        errorCode = true;
        return errorCode;
    }

    short commandNumber = userInput(&errorCode);
    if (commandNumber == -1) {
        return errorCode;
    }
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