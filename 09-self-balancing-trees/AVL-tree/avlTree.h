#pragma once

typedef struct NodeValue {
    const char* key;
    const char* value;
} NodeValue;

typedef struct Node Node;

Node* createTree(const char* key, const char* value, bool* errorCode);

void deleteTree(Node** root);

const char* searchByKey(Node* node, const char* key);

Node* addNode(Node* node, const char* key, const char* value, bool* isHeightChanged, bool* errorCode);

Node* deleteNode(Node* node, const char* key, bool* isHeightChanged, bool* errorCode);

NodeValue createNodeValue(const char* key, const char* value);