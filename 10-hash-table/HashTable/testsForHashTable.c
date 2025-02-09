#include "hashTable.h"
#include "testsForHashTable.h"

void runTheHashTableTests(bool* errorCode) {
    HashTable* hashTable = createHashTable(errorCode);
    if (*errorCode) {
        return;
    }
    addValueToHashTable(hashTable, "1", errorCode);
    addValueToHashTable(hashTable, "2", errorCode);
    addValueToHashTable(hashTable, "2", errorCode);
    addValueToHashTable(hashTable, "1", errorCode);
    addValueToHashTable(hashTable, "1", errorCode);
    bool test1 = getFrequencyFromHashTable(hashTable, "2", errorCode) == 2;
    bool test2 = getFrequencyFromHashTable(hashTable, "1", errorCode) == 3;
    bool test3 = getFrequencyFromHashTable(hashTable, "3", errorCode) == 0;
    if (*errorCode) {
        deleteHashTable(&hashTable, errorCode);
        return;
    }

    deleteHashTable(&hashTable, errorCode);
    if (!test1 || !test2 || !test3) {
        *errorCode = true;
    }
}