#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "list.h"
#include "testsForList.h"

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    runTheListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
}