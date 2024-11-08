#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "smartQSort.h"

bool testSmartQSort(bool *errorCode) {
    int testArray[21] = { 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
    smartQSort(testArray, 0, 20);
    for (int i = 0; i < 20; ++i) {
        if (testArray[i] > testArray[i + 1]) {
            printf("The testSmartQSort was not passed");
            *errorCode = true;
            return false;
        }
    }
    return true;
}

int main(void) {
    bool errorCode = false;
    int array[1000] = { 0 };
    int arrayLength = -1;

    if (!testSmartQSort(&errorCode)) {
        return errorCode;
    }

    readingAnArrayOfNumbersFromAFile(array, &arrayLength, &errorCode);

    printf("Unsorted array from file: ");
    for (int i = 0; i < arrayLength; ++i) {
        printf("%d ", array[i]);
    }

    smartQSort(array, 0, arrayLength - 1);
    printf("\nSorted array: ");
    for (int i = 0; i < arrayLength; ++i) {
        printf("%d ", array[i]);
    }

    return errorCode;
}