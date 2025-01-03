#define _CRT_SECURE_NO_WARNINGS

#include "workingWithAFile.h"
#include "testsWorkingWithAFile.h"

#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

void printReferenceInformation(void) {
    printf("\n------------------"
        "\n������� ����:"
        "\n0 - �����"
        "\n1 - �������� ������ (��� � �������)"
        "\n2 - ����������� ��� ��������� ������"
        "\n3 - ����� ������� �� �����"
        "\n4 - ����� ��� �� ��������"
        "\n5 - ��������� ������� ������ � ����\n");
}

short readUserInput(void) {
    printReferenceInformation();
    printf("\n������� �������: ");

    short functionCode = -1;
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 5 || functionCode < 0 || scanfReturns != 1) {
        printf("\n������������ ����� �������, ���������� ��� ���\n");
        printReferenceInformation();
        while (getchar() != '\n');
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

void launchPhoneDirectory(struct NameAndPhoneNumber* records, short commandNumber, bool *errorCode) {
    if (commandNumber == 0) {
        printf("����� �� �����������...\n");
        return;
    }
    else if (commandNumber == 1) {
        printf("\n���������� ������\n\n");
        addANewContact(records);
        commandNumber = readUserInput();
        launchPhoneDirectory(records, commandNumber, errorCode);
    }
    else if (commandNumber == 2) {
        printAllAvailableRecords(records);
        commandNumber = readUserInput() ;
        launchPhoneDirectory(records, commandNumber, errorCode);
    }
    else if (commandNumber == 3) {
        char *name = readUserInputForSearchByName();
        searchByName(records, name);
        commandNumber = readUserInput();
        launchPhoneDirectory(records, commandNumber, errorCode);
    }
    else if (commandNumber == 4) {
        char *phone = readUserInputForSearchByPhone();
        searchByPhone(records, phone);
        commandNumber = readUserInput();
        launchPhoneDirectory(records, commandNumber, errorCode);
    }
    else if (commandNumber == 5) {
        saveToFile(records, "phoneDatabase.txt");
        commandNumber = readUserInput();
        launchPhoneDirectory(records, commandNumber, errorCode);
    }
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool errorCode = false;


    if (!testSearchByName()) {
        printf("���� testSearchByName �� �������");
        errorCode = true;
        return errorCode;
    }

    if (!testSearchByPhone()) {
        printf("���� testSearchByPhone �� �������");
        errorCode = true;
        return errorCode;
    }

    short commandNumber = readUserInput();
    struct NameAndPhoneNumber records = {
        .numberOfEntries = 0,
        .names = { { '\0' } },
        .phones = { { '\0' } }
    };

    readFromAFile(&records, "phoneDatabase.txt");
    launchPhoneDirectory(&records, commandNumber, &errorCode);
    while (errorCode) {
        launchPhoneDirectory(&records, commandNumber, &errorCode);
    }

    return errorCode;
}