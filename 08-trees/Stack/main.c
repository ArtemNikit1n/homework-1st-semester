#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "testsForStack.h"

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    runStackTest(&errorCode);
    return errorCode;
}