#pragma once

// The function accepts a string in postfix form and returns the result of the calculation.
// If the string contains an incorrect number of binary operations, the program will be terminated using assert
int calculate(const char* inputString, bool* errorCode);