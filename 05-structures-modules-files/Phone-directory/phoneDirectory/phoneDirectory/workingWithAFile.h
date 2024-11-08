#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 20
#define MAX_ENTRIES 100

// Структура для хранения данных о номерах и именах
struct NameAndPhoneNumber {
    char names[MAX_ENTRIES][MAX_NAME_LENGTH];
    char phones[MAX_ENTRIES][MAX_PHONE_LENGTH];
    int numberOfEntries;
};

// Добавляет имя и телефон в структуру NameAndPhoneNumber
void addANewContact(struct NameAndPhoneNumber* records);

// Читает данные, которые уже находились в файле, и добавляет их в структуру NameAndPhoneNumber
void readingFromAFile(struct NameAndPhoneNumber* records, const char *filename);

// Выводит содержимое структуры NameAndPhoneNumber с номерами и именами
void printAllAvailableRecords(struct NameAndPhoneNumber* records);

// Пользовательский ввод имени
char* userInputForSearchByName();

// Поиск телефона в структуре
bool searchByName(struct NameAndPhoneNumber* records, char *name);

// Пользовательский ввод номера телфона
char* userInputForSearchByPhone();

// Поиск имени в структуре
bool searchByPhone(struct NameAndPhoneNumber* records, char *phone);

// Функция для сохранения данных из структуры в файл
void saveToFile(struct NameAndPhoneNumber* records, const char *filename);