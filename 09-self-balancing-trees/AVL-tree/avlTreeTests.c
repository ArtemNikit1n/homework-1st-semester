#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "avlTree.h"
#include "avlTreeTests.h"

bool testDeleteTreeAndCreateTree(bool* errorCode) {
    Node* testNode1 = createTree("32", "abc", errorCode);
    deleteTree(&testNode1);
    testNode1 = createTree("456", "def", errorCode);
    bool test1 = strcmp(searchByKey(testNode1, "456"), "def") == 0;
    bool test2 = !(searchByKey(testNode1, "321"), "def") == NULL;
    deleteTree(&testNode1);
    deleteTree(&testNode1);

    return !*errorCode && test1 && test2 && testNode1 == NULL;
}

bool testAddingAndDeleteNode(bool* errorCode) {
    Node* root = createTree("o", "15", errorCode);
    bool isHeightChanged = false;

    root = addNode(root, "f", "6", &isHeightChanged, errorCode);
    isHeightChanged = false;
    root = addNode(root, "t", "20", &isHeightChanged, errorCode);
    isHeightChanged = false;
    root = addNode(root, "s", "19", &isHeightChanged, errorCode);
    isHeightChanged = false;
    root = addNode(root, "u", "21", &isHeightChanged, errorCode);
    isHeightChanged = false;
    root = addNode(root, "h", "8", &isHeightChanged, errorCode);
    isHeightChanged = false;

    if (*errorCode) {
        deleteTree(&root);
        return false;
    }

    bool test1 = searchByKey(root, "m") == NULL;
    bool test2 = strcmp(searchByKey(root, "h"), "8") == 0;
    bool test3 = strcmp(searchByKey(root, "t"), "20") == 0;
    bool test4 = strcmp(searchByKey(root, "o"), "15") == 0;

    if (*errorCode) {
        deleteTree(&root);
        return false;
    }
    deleteNode(root, "u", &isHeightChanged, errorCode);
    isHeightChanged = false;
    deleteNode(root, "t", &isHeightChanged, errorCode);
    isHeightChanged = false;
    bool test5 = searchByKey(root, "u") == NULL;
    bool test6 = searchByKey(root, "t") == NULL;

    if (*errorCode) {
        deleteTree(&root);
        return false;
    }

    root = addNode(root, "a", "1", &isHeightChanged, errorCode);
    isHeightChanged = false;
    root = addNode(root, "g", "7", &isHeightChanged, errorCode);
    isHeightChanged = false;
    root = addNode(root, "k", "11", &isHeightChanged, errorCode);
    isHeightChanged = false;
    root = addNode(root, "j", "10", &isHeightChanged, errorCode);
    isHeightChanged = false;

    isHeightChanged = false;
    deleteNode(root, "f", &isHeightChanged, errorCode);
    bool test7 = searchByKey(root, "f") == NULL;

    deleteTree(&root);
    return test1 && test2 && test3 && test4 && test5 && test6 && test7;
}

void runAVLTreeTests(bool* errorCode) {
    if (!testDeleteTreeAndCreateTree(errorCode)) {
        printf("DisposeAndCreate's test failed\n");
        if (*errorCode) {
            printf("Error code: 1\n");
            return;
        }
        printf("Error code: 0\n");
        *errorCode = true;
        return;
    }
    if (!testAddingAndDeleteNode(errorCode)) {
        printf("AddingAndReadingValues's test failed\n");
        if (*errorCode) {
            printf("Error code: 1\n");
            return;
        }
        printf("Error code: 0\n");
        *errorCode = true;
        return;
    }
}