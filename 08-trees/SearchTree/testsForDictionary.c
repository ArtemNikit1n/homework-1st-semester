#include <stdio.h>
#include <stdbool.h>

#include "dictionary.h"

void testDeleteTreeAndCreateTree(bool* errorCode) {
    Node* testNode1 = createTree(32, "abc", errorCode);
    deleteTree(&testNode1);
    testNode1 = createTree(456, "def", errorCode);
    bool test1 = strcmp(searchByKey(testNode1, 456), "def") == 0;
    bool test2 = !(searchByKey(testNode1, 321), "def") == NULL;
    deleteTree(&testNode1);
    deleteTree(&testNode1);
    if (*errorCode) {
        return;
    }

    if (!(test1 && test2 && testNode1 == NULL)) {
        *errorCode = true;
        return;
    }
}

void testAddingAndDeleteNode(bool* errorCode) {
    Node* root = createTree(15, "15", errorCode);

    root = addNode(root, 6, "6", errorCode);
    root = addNode(root, 20, "20", errorCode);
    root = addNode(root, 19, "19", errorCode);
    root = addNode(root, 21, "21", errorCode);
    root = addNode(root, 8, "8", errorCode);

    if (*errorCode) {
        deleteTree(&root);
        return false;
    }

    bool test1 = searchByKey(root, 88) == NULL;
    bool test2 = strcmp(searchByKey(root, 8), "8") == 0;
    bool test3 = strcmp(searchByKey(root, 20), "20") == 0;
    bool test4 = strcmp(searchByKey(root, 15), "15") == 0;

    if (*errorCode) {
        deleteTree(&root);
        return false;
    }
    deleteNode(root, 21, errorCode);
    deleteNode(root, 20, errorCode);
    bool test5 = searchByKey(root, 21) == NULL;
    bool test6 = searchByKey(root, 20) == NULL;

    if (*errorCode) {
        deleteTree(&root);
        return false;
    }

    root = addNode(root, 1, "1", errorCode);
    root = addNode(root, 7, "7", errorCode);
    root = addNode(root, 11, "11", errorCode);
    root = addNode(root, 10, "10", errorCode);

    deleteNode(root, 6, errorCode);
    bool test7 = searchByKey(root, 6) == NULL;

    deleteTree(&root);
    if (!(test1 && test2 && test3 && test4 && test5 && test6 && test7)) {
        *errorCode = true;
        return;
    }
}

void runTheDictionaryTests(bool* errorCode) {
    testDeleteTreeAndCreateTree(errorCode);
    if (*errorCode) {
        printf("Dictionary test FAILED\n");
        return;
    }
    testAddingAndDeleteNode(errorCode);
    if (*errorCode) {
        printf("Dictionary test FAILED\n");
        return;
    }
}