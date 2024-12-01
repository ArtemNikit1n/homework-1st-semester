#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "headerFile.h"

void printTheBackgroundInformation() {
    printf(
            "1 - Half qsort\n"
            "2 - Bubble and counting\n"
            "3 - Exponentiation\n"
            "4 - Fibonacci Numbers\n");
}

void startingTask(int taskNumber) {
    if (taskNumber == 1) {
        halfQsortTask();
    }
    else if (taskNumber == 2) {
        bubbleAndCountingTask();
    }
    else if (taskNumber == 3) {
        exponentiationTask();
    }
    else if (taskNumber == 4) {
        fibonacciNumbersTask();
    } else {
        printf("Input error");
        return;
    }
}

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int getTheFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    printTheBackgroundInformation();
    printf("Enter the task number:\n");
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 4 || functionCode < 1 || scanfReturns != 1) {
        printf("The task number is entered incorrectly, try again\n");
        printTheBackgroundInformation();
        clearBuffer();
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

int main() {
    int taskNumber = getTheFunctionCodeFromTheUser();
    startingTask(taskNumber);
    return 0;
}
