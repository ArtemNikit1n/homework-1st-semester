#include <stdio.h>
#include <stdbool.h>

#include "../Tree/tree.h"

NodeValue createValue(int key, char* value) {
    NodeValue nodeValue = { .value = value, .key = key };
    return nodeValue;
}

bool testDisposeAndCreate(bool* errorCode) {
    Node* testNode1 = createNode(createValue(0, '\0'), errorCode);
    NodeValue testValue1 = getValue(testNode1, errorCode);
    bool test1 = testValue1.key == 0 && testValue1.value == '\0';
    disposeNode(&testNode1);

    Node* testNode2 = createNode(createValue(32, "abc"), errorCode);
    NodeValue testValue2 = getValue(testNode2, errorCode);
    bool test2 = testValue2.key == 32 && testValue2.value == "abc";
    disposeNode(&testNode2);
    return !*errorCode && test1 && test2 && testNode2 == NULL && testNode1 == NULL;
}

bool testAddingAndReadingValues(bool* errorCode) {
    Node* testNode = createNode(createValue(0, "Root"), errorCode);
    Node* test1LeftChild = createNode(createValue(-123, "Left1"), errorCode);
    Node* test2LeftChild = createNode(createValue(-321, "Left2"), errorCode);
    Node* testRightChild = createNode(createValue(321, "Right"), errorCode);

    if (*errorCode) {
        disposeNode(&test2LeftChild);
        disposeNode(&testNode);
        return false;
    }

    addLeftChild(testNode, test1LeftChild, errorCode);
    addLeftChild(testNode, test2LeftChild, errorCode);

    bool test1 = *errorCode;
    *errorCode = false;
    Node* getLeftChildResult = getLeftChild(testNode, errorCode);
    NodeValue testValue1 = getValue(getLeftChildResult, errorCode);
    bool test2 = testValue1.key == -123 && testValue1.value == "Left1";

    addRightChild(testNode, testRightChild, errorCode);
    setValue(test1LeftChild, createValue(123, "Left"), errorCode);

    if (*errorCode) {
        disposeNode(&test2LeftChild);
        disposeNode(&testNode);
        return false;
    }

    NodeValue testValue2 = getValue(test1LeftChild, errorCode);
    NodeValue testValue3 = getValue(testRightChild, errorCode);
    bool test3 = testValue2.key == 123 && testValue2.value == "Left";
    bool test4 = testValue3.key == 321 && testValue3.value == "Right";

    disposeNode(&test2LeftChild);
    disposeNode(&testNode);

    return !*errorCode && test1 && test2 && test3 && test4;
}

void runTheTreeTests(bool* errorCode) {
    if (!testDisposeAndCreate(errorCode)) {
        printf("���� testDisposeAndCreate �� �������\n");
        if (*errorCode) {
            printf("��� ������: 1\n");
            return;
        }
        printf("��� ������: 0\n");
        *errorCode = true;
        return;
    }
    if (!testAddingAndReadingValues(errorCode)) {
        printf("���� testAddingAndReadingValues �� �������\n");
        if (*errorCode) {
            printf("��� ������: 1\n");
            return;
        }
        printf("��� ������: 0\n");
        *errorCode = true;
        return;
    }
}