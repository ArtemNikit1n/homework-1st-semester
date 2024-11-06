#include <stdbool.h>
#include <stdio.h>
#include <locale.h>

#include "theCyclicList.h"
#include "testsForList.h"

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;
    runTheListTests(&errorCode);
    if (errorCode) {
        return errorCode;
    }
    List* list = createList(&errorCode);
    add(list, 0, 1, &errorCode);
    add(list, 0, 2, &errorCode);
    removeListElement(list, 1, &errorCode);
    //removeListElement(list, 0, &errorCode);
    deleteList(&list);
    return errorCode;
}