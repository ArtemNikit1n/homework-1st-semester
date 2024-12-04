#pragma once

#include "../list/list.h"

// Builds a hash table with words from a file.
List** buildHashTable(List* hashTable[], const char* fileName, int *hashTableSize, bool* errorCode);

// Displaying words and their frequencies on the screen.
void printHashTable(List* hashTable[], int* hashTableSize, bool* errorCode);