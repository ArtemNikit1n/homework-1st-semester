#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

#include "../Tree/tree.h"
#include "../Tree/testsForTree.h"

void printNode(Node* node, bool* errorCode) {
    NodeValue value = getValue(node, errorCode);
    printf("'%d': %s\n", value.key, value.value);
}

int main(void) {
    setlocale(LC_ALL, "Ru-ru");
    bool errorCode = false;

    runTheTreeTests(&errorCode);
    return errorCode;
}