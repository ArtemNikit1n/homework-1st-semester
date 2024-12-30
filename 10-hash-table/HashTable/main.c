#include <stdio.h>
#include <stdlib.h>

#include "../list/testsForList.h"
#include "../list/list.h"
#include "hashTable.h"

void printStatisticsOnTable(List** hashTable, int *hashTableSize, bool *errorCode) {
    int numberOfFilledCells = 0;
    int maxLengthOfList = -1;
    int numberOfWords = 0;

    for (int i = 0; i < *hashTableSize; ++i) {
        if (hashTable[i] == NULL) {
            continue;
        }
        ++numberOfFilledCells;
        int currentLegthOfList = 0;

        Position j = next(first(hashTable[i], errorCode), errorCode);
        while (j != NULL) {
            j = next(j, errorCode);
            maxLengthOfList = max(maxLengthOfList, currentLegthOfList);
            ++currentLegthOfList;
            ++numberOfWords;
        }
    }

    float hashTableFillFactor = (float)numberOfWords / (float)*hashTableSize;
    float averageLengthOfList = (float)numberOfWords / (float)numberOfFilledCells;

    printf("\nHash table fill factor: %f\n"
        "The average length of the list: %f\n"
        "Maximum list length: %d\n", hashTableFillFactor, averageLengthOfList, maxLengthOfList);
}

int main(void) {
    bool errorCode = false;
    if (!runTheListTests(&errorCode)) {
        return errorCode;
    }

    int hashTableSize = 5;

    List** hashTable = calloc(hashTableSize, sizeof(List*));
    if (hashTable == NULL) {
        errorCode = true;
        return;
    }
    hashTable = buildHashTable(hashTable, "text.txt", &hashTableSize, &errorCode);

    printHashTable(hashTable, &hashTableSize, &errorCode);
    printStatisticsOnTable(hashTable, &hashTableSize, &errorCode);

    for (int i = 0; i < hashTableSize; ++i) {
        if (hashTable[i] != NULL) {
            deleteList(&hashTable[i]);
        }
    }
    free(hashTable);
}