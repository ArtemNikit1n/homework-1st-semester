#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../Tree/tree.h"
#include "../Stack/stack.h"

Node* buildTree(FILE* file, bool* errorCode) {
    Node* root = NULL;
    Stack* stack = createStack(errorCode);
    if (*errorCode) {
        return NULL;
    }

    const char numbers[] = "0123456789";

    while (!feof(file)) {
        int theCurrentCharacter = getc(file);
        if (theCurrentCharacter == ' ' || theCurrentCharacter == '(' || theCurrentCharacter == ')') {
            continue;
        }

        bool isDigit = false;
        if (strchr(numbers, theCurrentCharacter) != NULL) {
            ungetc(theCurrentCharacter, file);
            fscanf(file, "%d", &theCurrentCharacter);
            isDigit = true;
        }

        Node* node = createNode(theCurrentCharacter, errorCode);
        if (*errorCode) {
            return NULL;
        }

        if (root == NULL) {
            root = node;
            addLeftChild(node, NULL, errorCode);
            addRightChild(node, NULL, errorCode);

            push(stack, node, errorCode);
            if (*errorCode) {
                return NULL;
            }
            continue;
        }

        Node* previousOperation = getStackValue(stack);
        if (getLeftChild(previousOperation, errorCode) == NULL) {
            addLeftChild(previousOperation, node, errorCode);
            if (*errorCode) {
                return NULL;
            }
        } 
        else if (getRightChild(previousOperation, errorCode) == NULL) {
            addRightChild(previousOperation, node, errorCode);
            pop(stack, errorCode);
            if (*errorCode) {
                return NULL;
            }
        }

        if (!isDigit) {
            push(stack, node, errorCode);
        }
    }
    return root;
}

void printAPostfixEntry(const Node* node, bool* errorCode) {
    if (node == NULL) {
        return '\0';
    }

    printAPostfixEntry(getLeftChild(node, errorCode), errorCode);
    if (*errorCode) {
        return;
    }

    printAPostfixEntry(getRightChild(node, errorCode), errorCode);
    if (*errorCode) {
        return;
    }

    if (getLeftChild(node, errorCode) == NULL && getRightChild(node, errorCode) == NULL) {
        printf("%d ", getValue(node, errorCode));
    } else {
        printf("%c ", getValue(node, errorCode));
    }
}

int calculateItFromTheTree(Node* node, bool* errorCode) {
    if (*errorCode) {
        return 0;
    }

    if (getLeftChild(node, errorCode) == NULL && getRightChild(node, errorCode) == NULL) {
        return getValue(node, errorCode);
    }

    if (getValue(node, errorCode) == '+') {
        return calculateItFromTheTree(getRightChild(node, errorCode), errorCode) + calculateItFromTheTree(getLeftChild(node, errorCode), errorCode);
    }
    if (getValue(node, errorCode) == '-') {
        return calculateItFromTheTree(getRightChild(node, errorCode), errorCode) - calculateItFromTheTree(getLeftChild(node, errorCode), errorCode);
    }
    if (getValue(node, errorCode) == '*') {
        return calculateItFromTheTree(getRightChild(node, errorCode), errorCode) * calculateItFromTheTree(getLeftChild(node, errorCode), errorCode);
    }
    if (getValue(node, errorCode) == '/') {
        if (calculateItFromTheTree(getRightChild(node, errorCode), errorCode) == 0) {
            *errorCode = true;
            return 0;
        }
        return calculateItFromTheTree(getRightChild(node, errorCode), errorCode) / calculateItFromTheTree(getLeftChild(node, errorCode), errorCode);
    }
}