#pragma once

#include "../Tree/tree.h"

typedef Node* Value;

// A structure with a pointer to the beginning of the stack.
typedef struct Stack Stack;

// Allocating memory for a new stack.
Stack* createStack(bool* errorCode);

// Deletes the stack
void deleteStack(Stack** stackDoublePointer);

// Checking whether the stack contains at least one element.
bool isEmpty(Stack* stack);

// Adds an element to the end of the stack.
void push(Stack* stack, Value value, bool* errorCode);

// Removes an element from the beginning of the stack.
// Returns a deleted value.
Value pop(Stack* stack, bool* errorCode);

// Returns the value of the stack head.
Value getStackValue(Stack* stack);