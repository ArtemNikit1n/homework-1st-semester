#include <stdlib.h>
#include <stdbool.h>

#include "../Tree/tree.h"

typedef struct Node {
    NodeValue value;
    struct Node* leftChild;
    struct Node* rightChild;
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

void addLeftChild(Node* node, Node* child, bool* errorCode) {
    if (node->leftChild != NULL) {
        disposeNode(&node->leftChild);
    }
    if (node == NULL) {
        *errorCode = true;
        return;
    }
    node->leftChild = child;
}

void addRightChild(Node* node, Node* child, bool* errorCode) {
    if (node->rightChild != NULL) {
        disposeNode(&node->rightChild);
    }
    if (node == NULL) {
        *errorCode = true;
        return;
    }
    node->rightChild = child;
}

Node* getLeftChild(Node* node, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    return node->leftChild;
}

Node* getRightChild(Node* node, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    return node->rightChild;
}

NodeValue getValue(Node* node, bool* errorCode) {
    if (node == NULL) {
        NodeValue incorrectNodeValues = -1;
        *errorCode = true;
        return incorrectNodeValues;
    }
    return node->value;
}

void setValue(Node* node, NodeValue value, bool* errorCode) {
    if (node == NULL) {
        *errorCode = true;
        return;
    }
    node->value = value;
}

void disposeNode(Node** node) {
    if (*node == NULL) {
        return;
    }
    disposeNode((&(*node)->leftChild));
    disposeNode((&(*node)->rightChild));
    free(*node);
    *node = NULL;
}

Node* copyNode(const Node* source, bool* errorCode) {
    if (source == NULL) {
        *errorCode = true;
        return NULL;
    }

    Node* destination = createNode(source->value, errorCode);
    if (*errorCode) {
        return NULL;
    }

    if (source->leftChild != NULL) {
        destination->leftChild = copyNode(source->leftChild, errorCode);
        if (*errorCode) {
            disposeNode(&destination);
            return NULL;
        }
    }
    if (source->rightChild != NULL) {
        destination->rightChild = copyNode(source->rightChild, errorCode);
        if (*errorCode) {
            disposeNode(&destination);
            return NULL;
        }
    }
    return destination;
}