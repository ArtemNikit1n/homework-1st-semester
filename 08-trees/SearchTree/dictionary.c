#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

typedef struct {
    char* value;
    int key;
} NodeValue;

typedef struct Node {
    NodeValue value;
    Node* left;
    Node* right;
} Node;

Node* createNode(NodeValue value, bool* errorCode) {
    Node* node = calloc(1, sizeof(Node));
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    node->value = value;
    return node;
}

Node* createTree(const int key, const char* value, bool* errorCode) {
    Node* root = calloc(1, sizeof(Node));
    if (root == NULL) {
        *errorCode = true;
        return NULL;
    }
    root->value.key = key;

    const char* copyOfValue = strdup(value);
    if (copyOfValue == NULL) {
        free(root);
        *errorCode = true;
        return NULL;
    }
    root->value.value = copyOfValue;
    return root;
}

void deleteTree(Node** root) {
    if (*root == NULL) {
        return;
    }
    deleteTree((&(*root)->left));
    deleteTree((&(*root)->right));

    if ((*root)->value.value != NULL) {
        free((*root)->value.value);
    }

    free(*root);
    *root = NULL;
}

Node* addNode(Node* node, const int key, const char* value, bool* errorCode) {
    if (key == node->value.key) {
        node->value.value = value;
        return node;
    }

    if (node->left == NULL && key < node->value.key) {
        Node* newNode = createTree(key, value, errorCode);
        if (*errorCode) {
            return node;
        }
        node->left = newNode;
        return node;
    }
    else if (node->right == NULL && key > node->value.key) {
        Node* newNode = createTree(key, value, errorCode);
        if (*errorCode) {
            return node;
        }
        node->right = newNode;
        return node;
    }

    if (key > node->value.key) {
        addNode(node->right, key, value, errorCode);
        return node;
    }
    if (key < node->value.key) {
        addNode(node->left, key, value, errorCode);
        return node;
    }
}

char* searchByKey(Node* node, const int key) {
    if (node == NULL) {
        return NULL;
    }

    if (node->value.key == key) {
        return node->value.value;
    }

    if ((node->left == NULL && node->value.key > key) || (node->right == NULL && node->value.key < key)) {
        return NULL;
    }

    const char* foundValue = NULL;
    if (node->value.key < key) {
        foundValue = searchByKey(node->right, key);
    }
    if (node->value.key > key) {
        foundValue = searchByKey(node->left, key);
    }
    return foundValue;
}

Node* copyNode(const Node* source, bool* errorCode) {
    if (source == NULL) {
        *errorCode = true;
        return NULL;
    }

    Node* destination = createTree(source->value.key, source->value.value, errorCode);
    if (*errorCode) {
        return NULL;
    }

    return destination;
}

Node* deleteNode(Node* node, const int key, bool* errorCode) {
    if (*errorCode) {
        return node;
    }

    if (node->value.key == key) {
        if (node->left == NULL && node->right == NULL) {
            return NULL;
        }
        if (node->left != NULL && node->right == NULL) {
            return node->left;
        }
        if (node->left == NULL && node->right != NULL) {
            return node->right;
        }
        if (node->left != NULL && node->right != NULL) {
            Node* replacementNode = deleteNode(node, node->right->value.key, errorCode);
            Node* saveNode = copyNode(node, errorCode);
            node->value.key = replacementNode->value.key;
            node->value = replacementNode->value;
            free(replacementNode);
            return saveNode;
        }
    }

    if (node->left == NULL && node->right == NULL && strcmp(node->value.key, key) != 0) {
        return node;
    }

    Node* returnedNode = NULL;
    if (node->value.key < key) {
        returnedNode = deleteNode(node->right, key, errorCode);

        if (returnedNode == NULL) {
            Node* saveDeletedNode = copyNode(node->right, errorCode);
            deleteTree(&(node->right));
            node->right = NULL;
            return saveDeletedNode;
        }
        else if (returnedNode == node->right->left || returnedNode == node->right->right) {
            Node* saveDeletedNode = copyNode(node->right, errorCode);
            free(node->right->value.value);
            free(node->right);
            node->right = returnedNode;
            return saveDeletedNode;
        }
        return returnedNode;
    }
    if (node->value.key > key) {
        returnedNode = deleteNode(node->left, key, errorCode);

        if (returnedNode == NULL) {
            Node* saveDeletedNode = copyNode(node->left, errorCode);
            deleteTree(&(node->left));
            node->left = NULL;
            return saveDeletedNode;
        }
        else if (returnedNode == node->left->left || returnedNode == node->left->right) {
            Node* saveDeletedNode = copyNode(node->left, errorCode);
            free(node->left->value.value);
            node->left = returnedNode;
            return saveDeletedNode;
        }
        return returnedNode;
    }
    if (returnedNode != NULL) {
        deleteTree(&returnedNode);
    }
    return node;
}