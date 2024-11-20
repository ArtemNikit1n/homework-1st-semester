#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "stack.h"

typedef struct StackElement {
    int value;
    struct StackElement* next;
} StackElement;

struct Stack {
    StackElement* head;
};

Stack* createStack(bool *errorCode) {
    Stack* stack = (Stack*)calloc(1, sizeof(Stack));
    if (NULL == stack) {
        *errorCode = true;
        return NULL;
    }
    return stack;
}

void deleteStack(Stack** stackDoublePointer) {
    Stack* stack = *stackDoublePointer;
    while (stack->head != NULL) {
        StackElement* next = stack->head->next;
        free(stack->head);
        stack->head = next;
    }
    free(stack);
    *stackDoublePointer = NULL;
}

bool isEmpty(Stack* stack) {
    return NULL == stack->head;
}

void push(Stack* stack, int value, bool *errorCode) {
    StackElement* element = calloc(1, sizeof(StackElement));
    if (NULL == element) {
        *errorCode = true;
        return;
    }
    element->value = value;
    element->next = stack->head;
    stack->head = element;
}

int pop(Stack* stack, bool *errorCode) {
    if (stack->head == NULL) {
        *errorCode = true;
        return 0;
    }
    StackElement* tmp = stack->head;
    int value = stack->head->value;
    stack->head = stack->head->next;
    free(tmp);
    return value;
}