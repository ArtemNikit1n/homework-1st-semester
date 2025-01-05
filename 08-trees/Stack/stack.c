#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "stack.h"
#include "../Tree/tree.h"

typedef struct StackElement {
    Value value;
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

void deleteStack(Stack** stack) {
    while ((*stack)->head != NULL) {
        StackElement* next = (*stack)->head->next;
        free((*stack)->head);
        (*stack)->head = next;
    }
    free((*stack));
    *stack = NULL;
}

bool isEmpty(Stack* stack) {
    return NULL == stack->head;
}

void push(Stack* stack, Value value, bool *errorCode) {
    StackElement* element = calloc(1, sizeof(StackElement));
    if (NULL == element) {
        *errorCode = true;
        return;
    }
    element->value = value;
    element->next = stack->head;
    stack->head = element;
}

Value pop(Stack* stack, bool *errorCode) {
    if (stack->head == NULL) {
        *errorCode = true;
        return 0;
    }
    StackElement* tmp = stack->head;
    Value value = stack->head->value;
    stack->head = stack->head->next;
    free(tmp);
    return value;
}

Value getStackValue(Stack* stack) {
    if (stack == NULL || stack->head == NULL) {
        return NULL;
    }
    return stack->head->value;
}