#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "headerFile.h"

#define _CRT_SECURE_NO_WARNINGS

bool startingTask(short taskNumber, bool errorCode) {
    if (taskNumber == 1) {
        errorCode = theMostCommonElementTask();
        return errorCode;
    }
    else if (taskNumber == 2) {
        errorCode = searchTask();
        return errorCode;
    }
    else if (taskNumber == 3) {
        errorCode = smartQSortTask();
        return errorCode;
    }
    else {
        printf("Incorrect task number\n");
        errorCode = true;
        return errorCode;
    }
}

int main() {
    char strTaskNumber[2];
    char* endptrTaskNumber = NULL;
    short taskNumber = 0;
    bool errorCode = false;

    printf("Enter the task number from 1 to 3:\n");
    if (fgets(strTaskNumber, sizeof(strTaskNumber), stdin) == NULL) {
        printf("Input error\n");
        errorCode = true;
        return errorCode;
    }

    taskNumber = strtol(strTaskNumber, &endptrTaskNumber, 10);
    if (taskNumber <= 0 || taskNumber >= 4 || *endptrTaskNumber != '\0') {
        printf("Incorrect task number\n");
        errorCode = true;
        return errorCode;
    }

    return startingTask(taskNumber, errorCode);
}