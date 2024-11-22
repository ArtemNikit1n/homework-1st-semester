#include <stdio.h>
#include <locale.h>
#include <stdlib.h>

#include "../Stack/stack.h"
#include "advancedBracketBalance.h"
#include "userInput.h"
#include "testsForAdvancedBracketBalance.h"
#include "../Stack/testsForStack.h"

int main(void) {
    setlocale(LC_ALL, "Ru-ru");

    bool errorCode = false;

    runStackTest(&errorCode);
    if (errorCode) {
        return errorCode;
    }

    if (!testAdvancedBracketBalance(&errorCode) || errorCode) {
        printf("Тесты advancedBracketBalance не пройдены\n"); {
            errorCode = true;
            return errorCode;
        }
    }

    printf("Введите строку:\n");
    char* inputString = userInput(&errorCode);

    if (!checkBracketBalance(inputString, &errorCode)) {
        printf("Баланс скобок не соблюдён");
    } else {
        printf("Баланс скобок не нарушен");
    }
    free(inputString);

    return errorCode;
}