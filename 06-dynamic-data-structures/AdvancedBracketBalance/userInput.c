#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <stdbool.h>

char* userInput(bool *errorCode) {
    char *inputString = (char *)calloc(1, sizeof(char));
    if (inputString == NULL) {
        printf("Ошибка выделения памяти, попробуйте позже\n");
        return;
    }

    size_t bufferSize = 1;
    size_t lineLength = 0;

    while (true) {
        char oneCharacter = getchar();

        if (oneCharacter == '\n') {
            break;
        }

        if (lineLength + 1 >= bufferSize) {
            bufferSize *= 2;
            char* tmp = (char*)realloc(inputString, bufferSize * sizeof(char));
            if (tmp == NULL) {
                printf("Ошибка выделения памяти, попробуйте позже\n");
                *errorCode = true;
                return NULL;
            }
            inputString = tmp;
        }
        inputString[lineLength++] = oneCharacter;
    }

    inputString[lineLength] = '\0';
    return inputString;
}