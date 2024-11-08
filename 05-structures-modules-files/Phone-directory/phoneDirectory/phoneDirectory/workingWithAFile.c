#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "workingWithAFile.h"

void saveToFile(struct NameAndPhoneNumber* records, const char* filename) {
    FILE* file = fopen(filename, "w");
    assert(file != NULL);

    if (records->numberOfEntries == 0) {
        printf("\nНа текущий момент записи отсутствуют\n");
        return;
    }
    for (int i = 0; i < records->numberOfEntries; ++i) {
        fprintf(file, "%s - %s\n", records->names[i], records->phones[i]);
    }
    printf("\nКонтакты успешно сохранены в файл\n");
}

void addANewContact(struct NameAndPhoneNumber* records) {
    char name[MAX_NAME_LENGTH] = { "\0" };
    char phone[MAX_PHONE_LENGTH] = { "\0" };
    bool theInputIsSuccessful = false;
    bool contactAdded = false;

    printf("Введите имя нового контакта:\n");
    getchar();
    fscanf(stdin, "%s", name);
    if (strlen(name) >= MAX_NAME_LENGTH - 1) {
        printf("Слишком много символов в имени, попробуйте ещё раз\n");
        addANewContact(records);
        return;
    }

    printf("Введите номер телефона:\n");
    getchar();
    fscanf(stdin, "%s", phone);
    if (strlen(phone) >= MAX_PHONE_LENGTH - 1) {
        printf("Слишком много символов в номере телефона, попробуйте ещё раз\n");
        addANewContact(records);
        return;
    }

    printf("Проверьте правильно ли введена информация о контакте\n%s - %s\n", name, phone);
    printf("0 - Я хочу внести изменения\n1 - Всё верно\n");
    while (!theInputIsSuccessful) {
        char input[5];
        scanf("%s", &input);
        if (input[0] == '1' && input[1] == '\0') {
            theInputIsSuccessful = true;
            contactAdded = true;
        }
        else if (input[0] == '0' && input[1] == '\0') {
            theInputIsSuccessful = true;
            contactAdded = false;
        }
        else {
            theInputIsSuccessful = false;
            printf("Неверный ввод. Введите 1 или 0.\n");
        }
    }

    if (contactAdded == false) {
        addANewContact(records);
    } else {
        strcpy(records->names[records->numberOfEntries], name);
        strcpy(records->phones[records->numberOfEntries], phone);
        records->numberOfEntries++;
        printf("Контакт создан!\n");
        return;
    }
}

void readingFromAFile(struct NameAndPhoneNumber* records, const char *filename) {
    FILE* file = fopen(filename, "r");
    assert(file != NULL);

    char name[MAX_NAME_LENGTH];
    char phone[MAX_PHONE_LENGTH];
    records->numberOfEntries = 0;

    while (fscanf(file, "%s - %s\n", name, phone) == 2) { 
        strcpy(records->names[records->numberOfEntries], name);
        strcpy(records->phones[records->numberOfEntries], phone);
        records->numberOfEntries++;
    }
    fclose(file);
}

char* userInputForSearchByName() {
    bool theInputWasSuccessful = false;
    char *name = NULL;

    while (!theInputWasSuccessful) {
        name = (char*)calloc(MAX_NAME_LENGTH + 1, sizeof(char));
        assert(name != NULL);

        printf("\nВведите имя искомого контакта:\n\n");
        getchar();
        fscanf(stdin, "%s", name);
        if (strlen(name) >= MAX_NAME_LENGTH - 1) {
            printf("Слишком много символов в имени, попробуйте ещё раз\n");
            free(name);
            name = NULL;
        } else {
            theInputWasSuccessful = true;
        }
    }
    return name;
}

bool searchByName(struct NameAndPhoneNumber* records, char *name) {
    bool thePhoneWasFound = false;

    for (int i = 0; i < records->numberOfEntries; ++i) {
        if (strcmp(name, &records->names[i]) == 0) {
            printf("%s\n", records->phones[i]);
            thePhoneWasFound = true;
        }
    }
    if (!thePhoneWasFound) {
        printf("Телефон не найден\n");
    }
    return thePhoneWasFound;
}

char* userInputForSearchByPhone() {
    bool theInputWasSuccessful = false;
    char *phone = NULL;

    while (!theInputWasSuccessful) {
        phone = (char *)calloc(MAX_PHONE_LENGTH + 1, sizeof(char));
        assert(phone != NULL);

        printf("\nВведите телефон искомого контакта:\n\n");
        getchar();
        fscanf(stdin, "%s", phone);
        if (strlen(phone) >= MAX_PHONE_LENGTH - 1) {
            printf("Слишком длинный номер телефона, попробуйте ещё раз\n");
            free(phone);
            phone = NULL;
        } else {
            theInputWasSuccessful = true;
        }
    }
    return phone;
}

bool searchByPhone(struct NameAndPhoneNumber* records, char *phone) {
    bool theNameWasFound = false;

    for (int i = 0; i < records->numberOfEntries; ++i) {
        if (strcmp(phone, &records->phones[i]) == 0) {
            printf("%s\n", records->names[i]);
            theNameWasFound = true;
        }
    }
    if (!theNameWasFound) {
        printf("Имя не найдено\n");
    }
    return theNameWasFound;
}

void printAllAvailableRecords(struct NameAndPhoneNumber *records) {
    if (records->numberOfEntries == 0) {
        printf("\nНа текущий момент записи отсутствуют\n");
        return;
    }
    printf("\nТекущие записи (в том числе не содержащиеся в файле):\n\n");
    for (int i = 0; i < records->numberOfEntries; ++i) {
        printf("%d. %s - %s\n", i + 1, records->names[i], records->phones[i]);
    }
    printf("\n* Для сохранения этих данных нажмите 5\n");
}