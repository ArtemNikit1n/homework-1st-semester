#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "avlTree.h"
#include "avlTreeTests.h"

void printTheBackgroundInformation() {
    printf(
        "0 - Exit\n"
        "1 - Add a value by key to the dictionary. If such a key already exists, the value is replaced with a new one.\n"
        "2 - Get the key value from the dictionary.\n"
        "3 - Check for the specified key.\n"
        "4 - Delete the specified key and its associated value from the dictionary.\n\n"
    );
}

char* getValueFromTheUser(bool* errorCode) {
    const int buffer = 101;
    char value[101] = { '\0' };

    scanf("%101s", value);
    while (strlen(value) == buffer) {
        printf("The string size is too large. Try again\n");
        while (getchar() != '\n');
        scanf("%101s", value);
    }
    return value;
}

int getFunctionCodeFromTheUser(void) {
    int functionCode = -1;
    printTheBackgroundInformation();
    int scanfReturns = scanf("%d", &functionCode);
    while (functionCode > 4 || functionCode < 0 || scanfReturns != 1) {
        printf("Incorrect number. Please try again:\n");
        printTheBackgroundInformation();
        while(getchar() != '\n');
        scanfReturns = scanf("%d", &functionCode);
    }
    return functionCode;
}

void launchAVLTree(int functionCode, bool* errorCode) {
    Node* root = NULL;
    bool isHeightChanged = false;

    while (functionCode != 0) {
        if (functionCode == 1) {
            printf("Enter the key:\n");
            const char* key = getValueFromTheUser(errorCode);
            printf("Enter the value:\n");
            const char* value = getValueFromTheUser(errorCode);

            if (root == NULL) {
                root = createTree(key, value, errorCode);
                if (*errorCode) {
                    *errorCode = false;
                    printf("Memory allocation error. Try again\n");
                    functionCode = getFunctionCodeFromTheUser();
                    continue;
                }
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
            root = addNode(root, key, value, &isHeightChanged, errorCode);
            if (*errorCode) {
                *errorCode = false;
                printf("Error. Try again later\n");
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
            isHeightChanged = false;
        }
        if (functionCode == 2) {
            printf("Enter the key:\n");
            const char* theKeyForTheSearch = getValueFromTheUser(errorCode);
            const char* theFoundString = searchByKey(root, theKeyForTheSearch);
            if (*errorCode) {
                *errorCode = false;
                printf("Error. Try again later\n");
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
            if (theFoundString != NULL) {
                printf("%s\n", theFoundString);
            }
            printf("The key was not found\n");
        }
        if (functionCode == 3) {
            printf("Enter the key:\n");
            const char* keyForSearch = getValueFromTheUser(errorCode);
            const char* theFoundString = searchByKey(root, keyForSearch);
            if (*errorCode) {
                *errorCode = false;
                printf("Error. Try again later\n");
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
            if (theFoundString != NULL) {
                printf("The key was found\n");
            }
            printf("The key was not found\n");
        }
        if (functionCode == 4) {
            printf("Enter the key:\n");
            const char* theKeyToDelete = getValueFromTheUser(errorCode);

            root = deleteNode(root, theKeyToDelete, &isHeightChanged, errorCode);
            if (*errorCode) {
                *errorCode = false;
                printf("Error. Try again later\n");
                functionCode = getFunctionCodeFromTheUser();
                continue;
            }
            isHeightChanged = false;
            printf("The value has been deleted!\n");
        }
        functionCode = getFunctionCodeFromTheUser();
    }
}

int main(void) {
    bool errorCode = false;
    runAVLTreeTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    launchAVLTree(getFunctionCodeFromTheUser(), &errorCode);

    return errorCode;
}