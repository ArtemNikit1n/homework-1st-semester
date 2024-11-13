#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "../Stack/stack.h"

int calculate(const char *inputString, bool* errorCode) {
    Stack* stack = createStack(errorCode);
    const char numbers[] = "0123456789";
    int i = 0;
    while (inputString[i] != '\0') {
        if (isdigit(inputString[i])) {
            int value = 0;
            while (inputString[i] != '\0' && isdigit(inputString[i])) {
                value = value * 10 + (inputString[i] - '0');
                ++i;
            }
            push(stack, value, errorCode);
            if (*errorCode) {
                deleteStack(&stack);
                return 0;
            }
        }

        while (inputString[i] == ' ') {
            ++i;
        }
        if (inputString[i] == '+') {
            int firstNumber = pop(stack, errorCode);
            int secondNumber = pop(stack, errorCode);
            push(stack, firstNumber + secondNumber, errorCode);
            if (*errorCode) {
                deleteStack(&stack);
                return 0;
            }
            ++i;
        }
        if (inputString[i] == '-') {
            int firstNumber = pop(stack, errorCode);
            int secondNumber = pop(stack, errorCode);
            push(stack, secondNumber - firstNumber, errorCode);
            if (*errorCode) {
                deleteStack(&stack);
                return 0;
            }
            ++i;
        }
        if (inputString[i] == '*') {
            int firstNumber = pop(stack, errorCode);
            int secondNumber = pop(stack, errorCode);
            push(stack, firstNumber * secondNumber, errorCode);
            if (*errorCode) {
                deleteStack(&stack);
                return 0;
            }
            ++i;
        }
        if (inputString[i] == '/') {
            int firstNumber = pop(stack, errorCode);
            int secondNumber = pop(stack, errorCode);
            if (*errorCode) {
                deleteStack(&stack);
                return 0;
            }
            if (firstNumber == 0) {
                *errorCode = true;
                deleteStack(&stack);
                return 0;
            }
            push(stack, secondNumber / firstNumber, errorCode);
            if (*errorCode) {
                deleteStack(&stack);
                return 0;
            }
            ++i;
        }
    }
    int result = pop(stack, errorCode);
    if (*errorCode) {
        deleteStack(&stack);
        return 0;
    }
    deleteStack(&stack);
    return result;
}