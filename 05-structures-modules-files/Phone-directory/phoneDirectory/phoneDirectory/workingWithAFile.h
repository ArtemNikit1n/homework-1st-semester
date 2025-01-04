#pragma once

#include <stdbool.h>

#define MAX_RECORD_LENGTH 50
#define MAX_ENTRIES 100

// Структура для хранения данных о номерах и именах.
struct NameAndPhoneNumber {
    char names[MAX_ENTRIES][MAX_RECORD_LENGTH];
    char phones[MAX_ENTRIES][MAX_RECORD_LENGTH];
    int numberOfEntries;
};

// Добавляет имя и телефон в структуру NameAndPhoneNumber.
void addANewContact(struct NameAndPhoneNumber* records);

// Читает данные, которые уже находились в файле, и добавляет их в структуру NameAndPhoneNumber. Возвращает false при удачном открытии файла.
bool readFromAFile(struct NameAndPhoneNumber* records, const char *filename);

// Выводит содержимое структуры NameAndPhoneNumber с номерами и именами.
void printAllAvailableRecords(struct NameAndPhoneNumber* records);

// Поиск телефона в структуре. Возвращает true, если телефон найден.
const char* searchByName(struct NameAndPhoneNumber* records, const char *name);

// Функция для получения телефона или строки от пользователя.
const char* getStringValueFromUser(void);

// Поиск имени в структуре. Возвращает true, если имя найдено.
const char* searchByPhone(struct NameAndPhoneNumber* records, const char *phone);

// Функция для сохранения данных из структуры в файл. Возвращает false при удачном открытии файла.
bool saveToFile(struct NameAndPhoneNumber* records, const char *filename);