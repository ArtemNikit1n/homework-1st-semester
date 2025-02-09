#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../list/list.h"
#include "hashTable.h"

struct HashTable {
    List** table;
    size_t size;
    size_t numberOfElements;
};

size_t getFrequencyFromHashTable(HashTable* hashTable, Key value, bool* errorCode) {
    if (hashTable == NULL || value == NULL) {
        *errorCode = true;
        return 0;
    }
    const size_t hash = hashStringPolynomial(value, hashTable->size);
    if (hashTable->table[hash] == NULL) {
        return 0;
    }

    List* list = hashTable->table[hash];
    for (Position i = next(first(list, errorCode), errorCode); i != NULL; i = next(i, errorCode)) {
        if (strcmp(getValue(i, errorCode), value) == 0) {
            if (*errorCode) {
                return 0;
            }
            return getFrequency(i, errorCode);
        }
    }
}

void printHashTable(HashTable* hashTable, bool *errorCode) {
    printf("<Word> - <Frequency>\n");
    for (int i = 0; i < hashTable->size; ++i) {
        if (hashTable->table[i] == NULL) {
            continue;
        }
        Position j = next(first(hashTable->table[i], errorCode), errorCode);
        while (j != NULL) {
            if (*errorCode) {
                return;
            }
            printf("%s - %d\n", getValue(j, errorCode), getFrequency(j, errorCode));
            j = next(j, errorCode);
        }
    }
}

int hashStringPolynomial(const char* word, const size_t tableSize) {
    const int coefficientOfMultiplication = 29;
    int polynomial = 0;
    for (int i = 0; word[i] != '\0'; ++i) {
        const unsigned int numberInAlphabet = word[i];
        polynomial = (polynomial * coefficientOfMultiplication + numberInAlphabet) % tableSize;
    }
    return polynomial;
}

double calculateFillFactor(HashTable* hashTable) {
    return (double)(hashTable->numberOfElements) / (double)(hashTable->size);
}

HashTable* doubleHashTable(HashTable* hashTable, bool* errorCode) {
    List* tableContents = createList(errorCode);
    if (*errorCode) {
        return NULL;
    }
    for (int i = 0; i < hashTable->size; ++i) {
        if (hashTable->table[i] != NULL) {
            for (Position j = next(first(hashTable->table[i], errorCode), errorCode); j != NULL; j = next(j, errorCode)) {
                add(tableContents, first(tableContents, errorCode), getValue(j, errorCode), errorCode);
                setFrequency(next(first(tableContents, errorCode), errorCode), getFrequency(j, errorCode), errorCode);
                if (*errorCode) {
                    deleteList(&tableContents);
                    return NULL;
                }
            }
            deleteList(&hashTable->table[i]);
        }
    }

    hashTable->size *= 2;
    List** memoryForNewTable = realloc(hashTable->table, hashTable->size * sizeof(List*));
    if (memoryForNewTable == NULL) {
        deleteList(&tableContents);
        *errorCode = true;
        return hashTable;
    }
    hashTable->table = memoryForNewTable;
    memset(hashTable->table, NULL, hashTable->size * sizeof(List*));

    for (Position i = next(first(tableContents, errorCode), errorCode); i != NULL; i = next(i, errorCode)) {
        while (getFrequency(i, errorCode) != 0) {
            addValueToHashTable(hashTable, getValue(i, errorCode), errorCode);
            setFrequency(i, getFrequency(i, errorCode) - 1, errorCode);
            if (*errorCode) {
                deleteList(&tableContents);
                return NULL;
            }
        }
    }
    deleteList(&tableContents);
    return hashTable;
}

void addValueToHashTable(HashTable* hashTable, Key value, bool* errorCode) {
    if (hashTable == NULL || strlen(value) > MAX_WORD_LENGTH) {
        *errorCode = true;
        return;
    }

    const size_t hash = hashStringPolynomial(value, hashTable->size);
    if (hashTable->table[hash] == NULL) {
        hashTable->table[hash] = createList(errorCode);
        if (*errorCode) {
            return;
        }
    }
    List* list = hashTable->table[hash];

    bool isStringRepeating = false;
    for (Position i = next(first(list, errorCode), errorCode); i != NULL; i = next(i, errorCode)) {
        if (strcmp(getValue(i, errorCode), value) == 0) {
            setFrequency(i, getFrequency(i, errorCode) + 1, errorCode);
            isStringRepeating = true;
            if (*errorCode) {
                deleteList(&list);
                return;
            }
        }
    }
    if (!isStringRepeating) {
        ++hashTable->numberOfElements;
        add(list, first(list, errorCode), value, errorCode);
        if (*errorCode) {
            deleteList(&list);
            return;
        }
    }

    double hashTableFillFactor = calculateFillFactor(hashTable);
    while (hashTableFillFactor > 1.1) {
        HashTable* newHashTable = doubleHashTable(hashTable, errorCode);
        if (*errorCode) {
            deleteList(&list);
            return;
        }
        hashTable = newHashTable;
        hashTableFillFactor = calculateFillFactor(hashTable);
    }
}

HashTable* createHashTable(bool* errorCode) {
    HashTable* hashTable = calloc(1, sizeof(HashTable));
    if (hashTable == NULL) {
        *errorCode = true;
        return NULL;
    }
    hashTable->size = HASH_TABLE_INITIAL_SIZE;
    hashTable->table = calloc(HASH_TABLE_INITIAL_SIZE, sizeof(List*));
    if (hashTable->table == NULL) {
        free(hashTable);
        *errorCode = true;
        return NULL;
    }
    return hashTable;
}

void deleteHashTable(HashTable** hashTable, bool* errorCode) {
    if (hashTable == NULL) {
        *errorCode = true;
        return;
    }
    if (*hashTable == NULL) {
        return;
    }
    if ((*hashTable)->table == NULL) {
        free(*hashTable);
        *hashTable = NULL;
        return;
    }
    for (size_t i = 0; i < (*hashTable)->size; ++i) {
        deleteList(&(*hashTable)->table[i]);
    }
    free(*hashTable);
    *hashTable = NULL;
}

size_t calculateMaxListLength(HashTable* hashTable, bool* errorCode) {
    size_t maxListLength = 0;
    for (int i = 0; i < hashTable->size; ++i) {
        if (hashTable->table[i] == NULL) {
            continue;
        }
        Position j = next(first(hashTable->table[i], errorCode), errorCode);
        if (*errorCode) {
            return 0;
        }
        size_t listLength = 0;
        while (j != NULL) {
            j = next(j, errorCode);
            ++listLength;
        }
        maxListLength = max(listLength, maxListLength);
    }
    return maxListLength;
}

double calculateAverageListLength(HashTable* hashTable) {
    size_t numberOfFilledCells = 0;
    for (size_t i = 0; i < hashTable->size; ++i) {
        if (hashTable->table[i] != NULL) {
            ++numberOfFilledCells;
        }
    }
    return ((double)hashTable->numberOfElements) / ((double)numberOfFilledCells);
}