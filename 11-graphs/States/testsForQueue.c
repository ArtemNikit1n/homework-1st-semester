#include "queue.h"

void testQueue(bool* errorCode) {
    Queue* queue = createQueue(errorCode);
    if (*errorCode) {
        deleteQueue(&queue);
        return;
    }
    enqueue(queue, 1, errorCode);
    enqueue(queue, 2, errorCode);
    if (*errorCode) {
        deleteQueue(&queue);
        return;
    }
    dequeue(queue, errorCode);
    dequeue(queue, errorCode);
    if (*errorCode) {
        deleteQueue(&queue);
        return;
    }
    bool testIsPassed = queueIsEmpty(queue);
    deleteQueue(&queue);
    if (!testIsPassed) {
        *errorCode = true;
        return;
    }
};