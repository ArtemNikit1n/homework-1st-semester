#include <stdio.h>
#include <stdlib.h>

#include "../list/testsForList.h"
#include "hashTable.h"
#include "testsForHashTable.h"

bool isOneOfSpecialCharacters(const char symbol) {
    const char specialCharacters[] = { ' ', ',', '.', '\n', '"', '?', '!', '(', ')' };
    int numberOfSpecialCharacters = sizeof(specialCharacters) / sizeof(specialCharacters[0]);
    for (int i = 0; i < numberOfSpecialCharacters; ++i) {
        if (symbol == specialCharacters[i]) {
            return true;
        }
    }
    return false;
}

void printStatisticsOnTable(HashTable* hashTable, bool *errorCode) {
    const double fillFactor = calculateFillFactor(hashTable);
    const size_t maxListLength = calculateMaxListLength(hashTable, errorCode);
    if (*errorCode) {
        return;
    }
    const double averageListLength = calculateAverageListLength(hashTable);
    printf("\nHash table fill factor: %f\n"
        "The average length of the list: %f\n"
        "Maximum list length: %d\n", fillFactor, averageListLength, maxListLength);
}

void fillInHashTable(HashTable* hashTable, const char* fileName, bool* errorCode) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        *errorCode = true;
        return;
    }
    char buffer[MAX_WORD_LENGTH] = { '\0' };

    char symbol = fgetc(file);
    int wordLength = 0;

    if (!isOneOfSpecialCharacters(symbol)) {
        buffer[wordLength] = symbol;
        ++wordLength;
    }
    while (symbol != EOF) {
        while (isOneOfSpecialCharacters(symbol)) {
            symbol = fgetc(file);
            continue;
        }
        symbol = fgetc(file);

        if (isOneOfSpecialCharacters(symbol)) {
            while (isOneOfSpecialCharacters(symbol)) {
                symbol = fgetc(file);
                continue;
            }
            if (wordLength >= MAX_WORD_LENGTH) {
                *errorCode = true;
                return;
            }
            addValueToHashTable(hashTable, buffer, errorCode);
            if (*errorCode) {
                fclose(file);
                return;
            }
            memset(buffer, 0, MAX_WORD_LENGTH);
            wordLength = 0;
        }
        buffer[wordLength] = symbol;
        ++wordLength;
    }
    fclose(file);
 }

int main(void) {
    bool errorCode = false;
    if (!runTheListTests(&errorCode)) {
        return errorCode;
    }
    runTheHashTableTests(&errorCode);
    if (errorCode) {
        printf("Tests hashTable FAILED");
        return errorCode;
    }

    HashTable* hashTable = createHashTable(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    fillInHashTable(hashTable, "text.txt", &errorCode);
    if (errorCode) {
        deleteHashTable(&hashTable, &errorCode);
        return errorCode;
    }

    printHashTable(hashTable, &errorCode);
    printStatisticsOnTable(hashTable, &errorCode);
    deleteHashTable(&hashTable, &errorCode);
    return errorCode;
}
