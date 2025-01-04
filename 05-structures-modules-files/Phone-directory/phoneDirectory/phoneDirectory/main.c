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
        "\nГлавное меню:"
        "\n0 - выйти"
        "\n1 - добавить запись (имя и телефон)"
        "\n2 - распечатать все имеющиеся записи"
        "\n3 - найти телефон по имени"
        "\n4 - найти имя по телефону"
        "\n5 - сохранить текущие данные в файл\n");
}

int readUserInput(void) {
    printReferenceInformation();
    printf("\nВведите команду: ");

    int functionCode = -1;
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 5 || functionCode < 0 || scanfReturns != 1) {
        printf("\nНекорректный номер команды, попробуйте ещё раз\n");
        printReferenceInformation();
        while (getchar() != '\n');
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

void launchPhoneDirectory(struct NameAndPhoneNumber* records, int commandNumber) {
    while (commandNumber != 0) {
        if (commandNumber == 1) {
            printf("\nДобавление записи\n\n");
            addANewContact(records);
            commandNumber = readUserInput();
        }
        else if (commandNumber == 2) {
            printAllAvailableRecords(records);
            commandNumber = readUserInput() ;
        }
        else if (commandNumber == 3) {
            printf("\nВведите имя искомого контакта:\n\n");
            const char* name = getStringValueFromUser();
            if (name == NULL) {
                printf("\nОшибка выделения памяти, попробуйте ещё раз");
                commandNumber = readUserInput();
                continue;
            }

            const char* foundPhone = searchByName(records, name);
            free(name);
            if (foundPhone == NULL) {
                printf("\nТелефон не найден");
            }
            printf("\n%s", foundPhone);
            commandNumber = readUserInput();
        }
        else if (commandNumber == 4) {
            printf("\nВведите телефон искомого контакта:\n\n");
            const char* phone = getStringValueFromUser();
            if (phone == NULL) {
                printf("\nОшибка выделения памяти, попробуйте ещё раз");
                commandNumber = readUserInput();
                continue;
            }

            const char* foundName = searchByPhone(records, phone);
            free(phone);
            if (foundName == NULL) {
                commandNumber = readUserInput();
                printf("\nИмя не найдено");
                continue;
            }
            printf("\n%s", foundName);
            commandNumber = readUserInput();
        }
        else if (commandNumber == 5) {
            if (saveToFile(records, "phoneDatabase.txt")) {
                printf("\nОшибка открытия файла, попробуйте ещё раз");
            }
            printf("\nКонтакты успешно сохранены в файл\n");
            commandNumber = readUserInput();
        }
    }
    printf("Выход из справочника...\n");

}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    if (!testSearchByName()) {
        printf("Тест testSearchByName не пройден");
        return true;
    }

    if (!testSearchByPhone()) {
        printf("Тест testSearchByPhone не пройден");
        return true;
    }

    int commandNumber = readUserInput();
    struct NameAndPhoneNumber records = {
        .numberOfEntries = 0,
        .names = { { '\0' } },
        .phones = { { '\0' } }
    };

    if (readFromAFile(&records, "phoneDatabase.txt")) {
        printf("\nОшибка открытия файла");
        return true;
    }
    launchPhoneDirectory(&records, commandNumber);

    return false;
}