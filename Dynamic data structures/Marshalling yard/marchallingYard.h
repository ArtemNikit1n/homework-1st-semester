#pragma once

#include <stdbool.h>

// Accepts a string in infix form, returns a postfix form.
char* infixToPostfix(const char* inputString, bool* errorCode);