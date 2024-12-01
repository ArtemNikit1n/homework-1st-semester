#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../list/list.h"

void printHashTable(List* hashTable[], bool *errorCode) {
    printf("<Word> - <Frequency>\n");
    for (int i = 0; i < 1000; ++i) {
        if (hashTable[i] == NULL) {
            continue;
        }
        Position j = next(first(hashTable[i], errorCode), errorCode);
        while (j != NULL) {
            printf("%s - %d\n", getValue(j, errorCode), getFrequency(j, errorCode));
            j = next(j, errorCode);
        }
    }
}

int hashStringPolynomial(const char* word, const int tableSize) {
    const int coefficientOfMultiplication = 29;
    int polynomial = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        const unsigned int numberInAlphabet = word[i];
        polynomial = (polynomial * coefficientOfMultiplication + numberInAlphabet) % tableSize;
    }
    return polynomial;
}

bool isSpecialCharacters(const char symbol) {
    const char specialCharacters[] = { ' ', ',', '.', '\n', '"', '?', '!', '(', ')'};
    int numberOfSpecialCharacters = sizeof(specialCharacters) / sizeof(specialCharacters[0]);
    for (int i = 0; i < numberOfSpecialCharacters; ++i) {
        if (symbol == specialCharacters[i]) {
            return true;
        }
    }
    return false;
}

void buildHashTable(List* hashTable[], const char* fileName, bool* errorCode) {
    FILE* file = fopen(fileName, "r");

    char* buffer = calloc(50, sizeof(char));
    if (buffer == NULL) {
        *errorCode = true;
        return;
    }

    char symbol = fgetc(file);
    int wordLength = 0;


    if (!isSpecialCharacters(symbol)) {
        buffer[wordLength] = symbol;
        ++wordLength;
    }
    while (symbol != EOF) {
        while (isSpecialCharacters(symbol)) {
            symbol = fgetc(file);
            continue;
        }
        symbol = fgetc(file);

        if (isSpecialCharacters(symbol)) {
            while (isSpecialCharacters(symbol)) {
                symbol = fgetc(file);
                continue;
            }

            int hash = hashStringPolynomial(buffer, 1000);
            if (hashTable[hash] == NULL) {
                hashTable[hash] = createList(errorCode);
            }

            bool isStringRepeating = false;
            for (Position i = next(first(hashTable[hash], errorCode), errorCode); i != NULL; i = next(i, errorCode)) {
                if (strcmp(getValue(i, errorCode), buffer) == 0) {
                    setFrequency(i, getFrequency(i, errorCode) + 1, errorCode);
                    free(buffer);
                    buffer = calloc(50, sizeof(char));
                    if (buffer == NULL) {
                        *errorCode = true;
                        return;
                    }
                    isStringRepeating = true;
                    break;
                }
            }
            if (!isStringRepeating) {
                add(hashTable[hash], first(hashTable[hash], errorCode), buffer, errorCode);
                buffer = calloc(50, sizeof(char));
                if (buffer == NULL) {
                    *errorCode = true;
                    return;
                }
            }
            wordLength = 0;
        }

        buffer[wordLength] = symbol;
        ++wordLength;
    }
    fclose(file);
}