#pragma once

#include <stdbool.h>

// The structure for the stack.
typedef struct Stack Stack;

// Allocating memory for a new stack.
Stack* createStack(bool* errorCode);

// Deletes the stack
void deleteStack(Stack** stackDoublePointer);

// Checking whether the stack contains at least one element.
bool isEmpty(Stack* stack);

// Adds an element to the end of the stack.
void push(Stack* stack, char value, bool* errorCode);

// Removes an element from the beginning of the stack.
// Returns a deleted value.
char pop(Stack* stack, bool* errorCode);