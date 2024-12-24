#include "queue.h"

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct QueueElement {
    int value;
    struct QueueElement* next;
} QueueElement;

typedef struct Queue {
    QueueElement* front;
    QueueElement* back;
} Queue;

Queue* createQueue(bool* errorCode) {
    Queue* queue = (Queue*)calloc(1, sizeof(Queue));
    if (queue == NULL) {
        errorCode = true;
        return NULL;
    }
    return queue;
}

void deleteQueue(Queue** queueDoublePointer) {
    if (queueDoublePointer == NULL || *queueDoublePointer == NULL) {
        return;
    }

    QueueElement* current = (*queueDoublePointer)->front;

    while (current != NULL) {
        QueueElement* next = current->next;
        free(current);
        current = next;
    }

    free(*queueDoublePointer);
    *queueDoublePointer = NULL;
}

void enqueue(Queue* queue, int value, bool* errorCode) {
    QueueElement* element = (QueueElement*)calloc(1, sizeof(QueueElement));
    if (element == NULL) {
        errorCode = true;
        return NULL;
    }
    element->value = value;
    if (queue->back == NULL) {
        queue->front = element;
        queue->back = element;
    }
    else {
        queue->back->next = element;
        queue->back = element;
    }
}

int dequeue(Queue* queue, bool* errorCode) {
    if (queue->front == NULL) {
        errorCode = true;
        return 0;
    }
    char value = queue->front->value;
    QueueElement* tmp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->back = NULL;
    }
    free(tmp);
    return value;
}

bool queueIsEmpty(Queue* queue) {
    return queue->back == NULL;
}