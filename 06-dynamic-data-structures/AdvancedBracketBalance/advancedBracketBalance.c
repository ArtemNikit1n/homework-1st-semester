#include <stdio.h>
#include <stdbool.h>

#include "../Stack/stack.h"

bool checkBracketBalance(const char* inputString, bool *errorCode) {
    Stack* stack = createStack(errorCode);
    bool balance = true;
    for (int i = 0; inputString[i] != '\0'; ++i) {
        if (inputString[i] == '(' || inputString[i] == '[' || inputString[i] == '{') {
            push(stack, inputString[i], errorCode);
            if (*errorCode) {
                deleteStack(&stack);
                return false;
            }
            continue;
        }
        if (inputString[i] == ')') {
            balance = pop(stack, errorCode) == '(';
            if (*errorCode || !balance) {
                deleteStack(&stack);
                return false;
            }
            continue;
        }
        if (inputString[i] == ']') {
            balance = pop(stack, errorCode) == '[';
            if (*errorCode || !balance) {
                deleteStack(&stack);
                return false;
            }
            continue;
        }
        if (inputString[i] == '}') {
            balance = pop(stack, errorCode) == '{';
            if (*errorCode || !balance) {
                deleteStack(&stack);
                return false;
            }
            continue;
        }
    }
    deleteStack(&stack);
    return balance;
}