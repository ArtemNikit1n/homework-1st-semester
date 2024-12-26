#include <stdio.h>
#include <stdbool.h>
#include "queue.h"

void testForEnqueueAndDequeue(bool *errorCode) {
    Queue* queue = createQueue(errorCode);
    if (*errorCode) {
        printf("Функция сработала с ошибкой\n");
        deleteQueue(&queue);
        return false;
    }
    enqueue(queue, 1, errorCode);
    enqueue(queue, 2, errorCode);
    if (*errorCode) {
        printf("Функция сработала с ошибкой\n");
        deleteQueue(&queue);
        return false;
    }
    dequeue(queue, errorCode);
    dequeue(queue, errorCode);
    if (*errorCode) {
        printf("Функция сработала с ошибкой\n");
        deleteQueue(&queue);
        return false;
    }
    bool testIsPassed = queueIsEmpty(queue);
    deleteQueue(&queue);
    if (!testIsPassed) {
        *errorCode = true;
        return;
    }
};
