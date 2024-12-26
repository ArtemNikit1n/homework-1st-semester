#include <stdio.h>
#include <stdbool.h>

#include "stack.h"

void testCreateStack(bool* errorCode) {
    Stack* testStack = createStack(errorCode);
    if (*errorCode) {
        return;
    }
    if (testStack == NULL) {
        *errorCode = true;
        return;
    }
    deleteStack(&testStack);
    if (testStack != NULL) {
        *errorCode = true;
        return;
    }
}

void testDeleteStack(bool* errorCode) {
    Stack* testStack = createStack(errorCode);
    if (*errorCode) {
        return;
    }
    push(testStack, 1, errorCode);
    push(testStack, 2, errorCode);
    push(testStack, 3, errorCode);
    if (*errorCode) {
        deleteStack(&testStack);
        return;
    }
    deleteStack(&testStack);
    if (testStack != NULL) {
        *errorCode = true;
        return;
    }
}

void testIsEmpty(bool* errorCode) {
    Stack* testStack = createStack(errorCode);
    if (*errorCode) {
        deleteStack(&testStack);
        return;
    }
    bool test1IsPassed = isEmpty(testStack);

    push(testStack, 1, errorCode);
    if (*errorCode) {
        deleteStack(&testStack);
        return;
    }
    bool test2IsPassed = !isEmpty(testStack);
    deleteStack(&testStack);
    if (!(test1IsPassed && test2IsPassed)) {
        *errorCode = true;
    }
}

void testPush(bool* errorCode) {
    Stack* testStack = createStack(errorCode);
    if (*errorCode) {
        deleteStack(&testStack);
        return;
    }
    push(testStack, 1, errorCode);
    push(testStack, 2, errorCode);
    push(testStack, 3, errorCode);
    if (*errorCode) {
        deleteStack(&testStack);
        return;
    }
    bool testIsPassed = !isEmpty(testStack);
    deleteStack(&testStack);
    if (!testIsPassed) {
        *errorCode = true;
    }
}

void testPop(bool* errorCode) {
    Stack* testStack = createStack(errorCode);
    if (*errorCode) {
        deleteStack(&testStack);
        return;
    }
    push(testStack, 1, errorCode);
    bool testIsPassed = pop(testStack, errorCode) == 1;
    if (*errorCode) {
        deleteStack(&testStack);
        return;
    }
    deleteStack(&testStack);
    if (!testIsPassed) {
        *errorCode = true;
    }
}

void runStackTest(bool* errorCode) {
    testCreateStack(errorCode);
    testDeleteStack(errorCode);
    testIsEmpty(errorCode);
    testPush(errorCode);
    testPop(errorCode);
}