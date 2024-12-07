#include <stdbool.h>
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <errno.h>

#define _CRT_SECURE_NO_WARNINGS

bool comparingTwoArrays(bool firstArray[], bool secondArray[], int arrayLength) {
    bool errorCode = true;
    for (int i = 0; i < arrayLength; ++i) {
        if (firstArray[i] != secondArray[i]) {
            errorCode = false;
            break;
        }
    }
    return errorCode;
}

void printBoolArray(bool boolArray[], int boolArrayLength) {
    for (int i = 0; i < boolArrayLength; ++i) {
        printf("%d", boolArray[i]);
    }
}

int exponentiationLogTime(int baseOfDegree, int exponent) {
    int result = 1;

    if (exponent == 0) {
        return result;
    }
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= baseOfDegree;
        }
        exponent /= 2;
        baseOfDegree *= baseOfDegree;
    }

    return result;
}

void binarySum(bool binaryFirstNumber[], bool binarySecondNumber[], bool binarySumArray[]) {
    bool theAdditionalTerm = 0;
    for (int i = 31; i >= 0; --i) {
        bool oneAndZero = (binaryFirstNumber[i] && !binarySecondNumber[i]) || (!binaryFirstNumber[i] && binarySecondNumber[i]);
        if (!binaryFirstNumber[i] && !binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 0;
                binarySumArray[i] = 1;
            } 
            else {
                binarySumArray[i] = 0;
            }
        }
        if (binaryFirstNumber[i] && binarySecondNumber[i]) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 1;
                binarySumArray[i] = 1;
            }
            else {
                theAdditionalTerm = 1;
                binarySumArray[i] = 0;
            }
        }
        if (oneAndZero) {
            if (theAdditionalTerm) {
                theAdditionalTerm = 1;
                binarySumArray[i] = 0;
            }
            else {
                binarySumArray[i] = 1;
            }
        }
    }
}

int conversionToDecimal(bool binaryNumber[]) {
    if (binaryNumber[0]) {
        int decimalNumber = -1;

        bool minusOne[32] = { 1 };
        binarySum(binaryNumber, minusOne, binaryNumber);
        for (int i = 1; i < 32; ++i) {
            decimalNumber -= !binaryNumber[i] * exponentiationLogTime(2, 31 - i);
        }
        return decimalNumber;
    } else {
        int decimalNumber = 0;

        for (int i = 1; i < 32; ++i) {
            decimalNumber += binaryNumber[i] * exponentiationLogTime(2, 31 - i);
        }
        return decimalNumber;
    }
}

void getBinaryNumber(int decimalNumber, bool binaryNumber[]) {
    for (int i = 0; i < 32; ++i) {
        if ((decimalNumber) & (1 << i)) {
            binaryNumber[31 - i] = 1;
        } else {
            binaryNumber[31 - i] = 0;
        }
    }
}

void userInput(int *firstNumber, int *secondNumber, bool *errorCode) {
    char strFirstNumber[100];
    char strSecondNumber[100];
    char* endptrFirstNumber = NULL;
    char* endptrSecondNumber = NULL;
    errno = 0;

    setlocale(LC_ALL, "Rus");

    printf("Введите первое число:\n");
    scanf("%s", strFirstNumber); 
    *firstNumber = (int)strtol(strFirstNumber, &endptrFirstNumber, 10);

    printf("Введите второе число:\n");
    scanf("%s", strSecondNumber);
    *secondNumber = (int)strtol(strSecondNumber, &endptrSecondNumber, 10);

    if (errno == ERANGE) {
        printf("Ошибка ввода");
        *errorCode = true;
    }

    if (*endptrFirstNumber != '\0' || *endptrSecondNumber != '\0') {
        printf("Ошибка ввода");
        *errorCode = true;
    }
}

void checkingTheAmountForStackOverflow(int firstNumber, int secondNumber, bool *errorCode) {
    if (firstNumber < 0 && secondNumber < 0 && abs(firstNumber) > INT_MAX + (secondNumber + 1)) {
        printf("Переполнение стека");
        *errorCode = true;
    }
    if (firstNumber > 0 && secondNumber > 0 && firstNumber > INT_MAX - secondNumber) {
        printf("Переполнение стека");
        *errorCode = true;
    }
}

bool testComparingTwoArrays() {
    bool firstArray[6] = { 1, 0, 0, 1, 0, 1 };
    bool secondArray[6] = { 0, 1, 1, 1, 0, 0 };

    return !comparingTwoArrays(firstArray, secondArray, 6) && comparingTwoArrays(firstArray, firstArray, 6);
}

bool testExponentiationLogTime() {
    bool test1ExponentiationLogTime = exponentiationLogTime(5, 2) == 25;
    bool test2ExponentiationLogTime = exponentiationLogTime(2, 20) == 1048576;
    return test1ExponentiationLogTime && test2ExponentiationLogTime;
}

bool testGetBinaryNumber() {
    int positiveNumber = 2048;
    int negativeNumber = -1025;
    bool positiveNumberArray[32] = { 0 };
    positiveNumberArray[20] = 1;
    bool negativeNumberArray[32] = { 0 };
    for (int i = 0; i < 32; i++) {
        negativeNumberArray[i] = 1;
    }
    negativeNumberArray[21] = 0;
    bool theResultIsForThePositive[32] = { 0 };
    bool theResultIsForTheNegative[32] = { 0 };
    getBinaryNumber(positiveNumber, theResultIsForThePositive);
    getBinaryNumber(negativeNumber, theResultIsForTheNegative);

    return comparingTwoArrays(positiveNumberArray, theResultIsForThePositive, 32) && comparingTwoArrays(negativeNumberArray, theResultIsForTheNegative, 32);
}

bool testBinarySum() {
    bool theFirstSummand[32] = { 0 };
    for (int i = 1; i < 32; i++) {
        theFirstSummand[i] = 1;
    }
    bool theSecondSummand[32] = { 0 };
    for (int i = 0; i < 32; i++) {
        theSecondSummand[i] = 1;
    }
    bool expectedResult[32] = { 0 };
    for (int i = 1; i < 31; i++) {
        expectedResult[i] = 1;
    }

    bool result[32] = { 0 };
    binarySum(theFirstSummand, theSecondSummand, result);
    return comparingTwoArrays(result, expectedResult, 32);
}

bool testConversionToDecimal() {
    bool positiveNumberArray[32] = { 0 };
    positiveNumberArray[20] = 1;
    bool negativeNumberArray[32] = { 0 };
    for (int i = 0; i < 32; i++) {
        negativeNumberArray[i] = 1;
    }
    negativeNumberArray[21] = 0;
    return conversionToDecimal(positiveNumberArray) == 2048 && conversionToDecimal(negativeNumberArray) == -1025;
}

int main(void) {
    int firstNumber = -1;
    int secondNumber = -1;
    int decimalSumNumber = -1;
    bool binaryFirstNumber[32] = { 0 };
    bool binarySecondNumber[32] = { 0 };
    bool binarySumArray[32] = { 0 };

    bool errorCode = false;

    setlocale(LC_ALL, "Rus");

    if (!testComparingTwoArrays()) {
        printf("Тест comparingTwoArrays не пройден\n");
        errorCode = true;
        return errorCode;
    }

    if (!testExponentiationLogTime()) {
        printf("Тест exponentiationLogTime не пройден\n");
        errorCode = true;
        return errorCode;
    }

    if (!testGetBinaryNumber()) {
        printf("Тест getBinaryNumber не пройден\n");
        errorCode = true;
        return errorCode;
    }

    if (!testBinarySum()) {
        printf("Тест binarySum не пройден\n");
        errorCode = true;
        return errorCode;
    }

    if (!testConversionToDecimal()) {
        printf("Тест conversionToDecimal не пройден\n");
        errorCode = true;
        return errorCode;
    }

    userInput(&firstNumber, &secondNumber, &errorCode);
    if (errorCode) {
        return errorCode;
    }
    checkingTheAmountForStackOverflow(firstNumber, secondNumber, &errorCode);
    if (errorCode) {
        return errorCode;
    }

    getBinaryNumber(firstNumber, binaryFirstNumber);
    getBinaryNumber(secondNumber, binarySecondNumber);
    binarySum(binaryFirstNumber, binarySecondNumber, binarySumArray);

    printf("Двоичное представление первого числа в дополнительном коде:\n");
    printBoolArray(binaryFirstNumber, 32);
    printf("\nДвоичное представление второго числа в дополнительном коде:\n");
    printBoolArray(binarySecondNumber, 32);
    printf("\nДвоичная сумма:\n");
    printBoolArray(binarySumArray, 32);
    decimalSumNumber = conversionToDecimal(binarySumArray);
    printf("\nДесятичная сумма:\n%d", decimalSumNumber);

    return errorCode;
}