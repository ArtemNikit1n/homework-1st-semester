#pragma once

#include "../Tree/tree.h"

// Adds a node to the binary search tree.
void addToTheDictionary(Node* node, const int key, const char* value, bool* errorCode);

// Searching for a node in the tree (if the key is not found, NULL will be returned).
char* findValueByTheKey(Node* node, const int key, bool* errorCode);

// Removes a key from the tree.
Node* deleteByKey(Node* node, const int key, bool* errorCode);
