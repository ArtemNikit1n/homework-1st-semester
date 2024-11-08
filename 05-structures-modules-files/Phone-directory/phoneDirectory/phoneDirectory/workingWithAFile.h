#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define MAX_NAME_LENGTH 100
#define MAX_PHONE_LENGTH 20
#define MAX_ENTRIES 100

// ��������� ��� �������� ������ � ������� � ������
struct NameAndPhoneNumber {
    char names[MAX_ENTRIES][MAX_NAME_LENGTH];
    char phones[MAX_ENTRIES][MAX_PHONE_LENGTH];
    int numberOfEntries;
};

// ��������� ��� � ������� � ��������� NameAndPhoneNumber
void addANewContact(struct NameAndPhoneNumber* records);

// ������ ������, ������� ��� ���������� � �����, � ��������� �� � ��������� NameAndPhoneNumber
void readingFromAFile(struct NameAndPhoneNumber* records, const char *filename);

// ������� ���������� ��������� NameAndPhoneNumber � �������� � �������
void printAllAvailableRecords(struct NameAndPhoneNumber* records);

// ���������������� ���� �����
char* userInputForSearchByName();

// ����� �������� � ���������
bool searchByName(struct NameAndPhoneNumber* records, char *name);

// ���������������� ���� ������ �������
char* userInputForSearchByPhone();

// ����� ����� � ���������
bool searchByPhone(struct NameAndPhoneNumber* records, char *phone);

// ������� ��� ���������� ������ �� ��������� � ����
void saveToFile(struct NameAndPhoneNumber* records, const char *filename);