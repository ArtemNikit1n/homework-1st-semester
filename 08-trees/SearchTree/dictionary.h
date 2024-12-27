#pragma once

#include <stdbool.h>

#pragma once

// Structure for node values.
typedef struct {
    char* value;
    int key;
} NodeValue;

// Tree Node.
typedef struct Node Node;

// Creates a tree.
Node* createTree(const int key, const char* value, bool* errorCode);

// Delete a tree.
void deleteTree(Node** root);

// Searches for a value by key.
char* searchByKey(Node* node, const int key);

// Adds a new value to the tree (if such a key exists, the value for the old key will be deleted).
Node* addNode(Node* node, const int key, const char* value, bool* errorCode);

// Deletes a node by key.
Node* deleteNode(Node* node, const int key, bool* errorCode);

// Creates a value that can be stored in the node.
NodeValue createNodeValue(const int key, const char* value);