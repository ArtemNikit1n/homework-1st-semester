#pragma once

#define MAX_WORD_LENGTH 50
#define HASH_TABLE_INITIAL_SIZE 10

#include <stdlib.h>
#include <stdbool.h>

typedef struct HashTable HashTable;

typedef char* Key;

// Create a hash table.
HashTable* createHashTable(bool* errorCode);

// Adds a value to the hash table.
void addValueToHashTable(HashTable* hashTable, Key value, bool* errorCode);

// Print words and their frequencies on the screen.
void printHashTable(HashTable* hashTable, bool* errorCode);

// Deletes the hash table.
void deleteHashTable(HashTable** hashTable, bool* errorCode);

// Counts the maximum length of nonempty lists.
size_t calculateMaxListLength(HashTable* hashTable, bool* errorCode);

// Calculates the length value averaged over all non-empty lists inside the segments.
double calculateAverageListLength(HashTable* hashTable);

// Calculate fill factor.
// The fill factor is calculated as the number of elements in the table divided by the number of segments.
double calculateFillFactor(HashTable* hashTable);

// Gives the frequency by key.
size_t getFrequencyFromHashTable(HashTable* hashTable, Key value, bool* errorCode);