#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../Tree/tree.h"

// Builds a parse tree based on the input file.
Node* buildTree(FILE* file, bool* errorCode);

// The function outputs a postfix entry in the parse tree to the console.
void printAPostfixEntry(const Node* node, bool* errorCode);

// The function calculates the value of the expression in the parse tree.
int calculateItFromTheTree(Node* node, bool* errorCode);