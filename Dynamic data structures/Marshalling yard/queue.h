#pragma once

// The structure indicating the beginning and end of the queue.
typedef struct Queue Queue;

// Adds a number to the top of the queue.
void enqueue(Queue* queue, char value, bool* errorCode);

// Removes a number from the end of the queue.
char dequeue(Queue* queue, bool* errorCode);

// Creates a queue.
Queue* createQueue(bool* errorCode);

// Checking whether the stack contains at least one element.
bool queueIsEmpty(Queue* queue);

// Deletes the queue.
void deleteQueue(Queue** queueDoublePointer);