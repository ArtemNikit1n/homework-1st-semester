#pragma once

#include <stdbool.h>

// A structure with a pointer to the beginning of the stack.
typedef struct Stack Stack;

// Allocating memory for a new stack.
Stack* createStack(bool* errorCode);

// Deletes the stack
void deleteStack(Stack** stackDoublePointer);

// Checking whether the stack contains at least one element.
bool isEmpty(Stack* stack);

// Adds an element to the end of the stack.
void push(Stack* stack, int value, bool* errorCode);

// Removes an element from the beginning of the stack.
// Returns a deleted value.
int pop(Stack* stack, bool* errorCode);