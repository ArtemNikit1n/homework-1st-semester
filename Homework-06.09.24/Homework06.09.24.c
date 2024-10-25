#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int arrayInput(int arrayNumbers[100]) {
    int lengthArrayNumbers = 0;

    printf("%s\n", "Enter the array size (<= 100):");
    scanf("%d", &lengthArrayNumbers);
    printf("%s\n", "Enter the numbers of the array:");

    for (int i = 0; i < lengthArrayNumbers; ++i) {
        scanf("%d", &arrayNumbers[i]);
    }
    return lengthArrayNumbers;
}

void nullElements() {
    // Задача 1

    int arrayNumbers[100];
    int nullCounter = 0;
    int lengthArrayNumbers = arrayInput(arrayNumbers);

    for (int i = 0; i < lengthArrayNumbers; ++i) {
        printf("%d ", arrayNumbers[i]);
        if (arrayNumbers[i] == 0) {
            ++nullCounter;
        }
    }
    printf("Number of zeros = %d\n", nullCounter);
}

// ********

void swap(int *first, int *second) {
    if (*first == *second) {
        return;
    }
    *first ^= *second;
    *second ^= *first;
    *first ^= *second;
}

void task2Swap() {
    // Задача 2

    int first = 0;
    int second = 0;

    printf("%s\n", "Enter first number:");
    scanf("%d", &first);

    printf("%s\n", "Enter second number:");
    scanf("%d", &second);

    swap(&first, &second);

    printf("First number: %d ; Second number: %d", first, second);
}

// ********

int division(const int a, const int b) {
    int modulA = abs(a);
    int modulB = abs(b);
    int answer = 0;

    while (modulA >= modulB) {
        modulA -= modulB;
        answer += 1;
    }

    if (((a < 0 && b > 0) || (a < 0 && b < 0)) && modulA == 0) {
        answer -= 1;
    }
    return answer;
}

void incompleteQuotient() {
    // Задача 3

    int a = 0;
    int b = 0;
    int answer = 0;

    printf("%s\n", "Enter a: ");
    scanf("%d", &a);

    printf("%s\n", "Enter b:");
    scanf("%d", &b);

    if (b != 0) {
        if (a >= 0 && b > 0) {
            answer = division(a, b);
        }
        if (a > 0 && b < 0) {
            answer = -division(a, b);
        }
        if (a < 0 && b > 0) {
            answer = -division(a, b);
            answer -= 1;
        }
        if (a < 0 && b < 0) {
            answer = division(a, b);
            answer += 1;
        }
        printf("Answer: %d", answer);
    } else {
        printf("%s\n", "You can't divide by zero!");
    }
}

// ********

void luckyTickets() {
    // Задача 4

    int amounts[28] = {0};
    int answer = 0;

    for (int number = 0; number < 1000; number++) {
        int hundreds = number / 100;
        int units = number % 10;
        int tens = (number - (100 * hundreds) - units) / 10;
        int sum = hundreds + tens + units;

        amounts[sum] += 1;
    }

    for (int i = 0; i < 28; i++) {
        amounts[i] *= amounts[i];
        answer += amounts[i];
    }
    printf("%d", answer);
}

// ********

bool checkingTheBalanceOfBrackets(const char string[]) {
    int balance = 0;
    int i = 0;
    while (string[i] != '\0') {
        if (balance < 0) {
            return false;
        }
        if (string[i] == '(') {
            balance += 1;
        }
        if (string[i] == ')') {
            balance -= 1;
        }
        ++i;
    }
    return balance == 0;
}

void balanceOfBrackets() {
    // Задача 5

    char string[100];

    printf("%s\n", "Enter a string with brackets:");
    scanf("%s", string);

    printf("Result: %d \n1 - means the brackets balance is satisfied"
           "\n0 - means it is not satisfied", checkingTheBalanceOfBrackets(string));
}

// ********

bool isItPrime(int number) {
    int div = 2;
    while (div * div <= number) {
        if (number % div == 0)
            return 0;
        div += 1;
    }
    return 1;
}

void primeNumbers() {
    // Задача 6

    int number = 0;

    printf("%s\n", "Enter number:");
    scanf("%d", &number);

    for (int i = 2; i <= number; i++) {
        if (isItPrime(i)) {
            printf("%d ", i);
        }
    }
}

// ********

int countingTheNumberOfOccurrences(const char s[], const char s1[]) {
    int occurrenceCounter = 0;

    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == s1[0]) {
            bool symbolsAreEqual = 1;
            for (int j = 0; s1[j] != '\0'; ++j) {
                if (s[i + j] != s1[j]) {
                    symbolsAreEqual = 0;
                    break;
                }
            }
            if (symbolsAreEqual == 1) {
                ++occurrenceCounter;
            }
        }
    }
    return occurrenceCounter;
}

void substring() {
    // Задача 7

    char s[100];
    char s1[100];

    printf("%s\n", "Enter S (<100):");
    scanf("%s", s);

    printf("%s\n", "Enter S1 (<100):");
    scanf("%s", s1);

    printf("Number of occurrences of the substring: %d", countingTheNumberOfOccurrences(s, s1));
}

// ********

void arrayReversal(int arrayNumbers[100], const int lengthArrayNumbers) {
    int middleOfTheArray = (int)(lengthArrayNumbers / 2);

    for (int i = 0; i <= middleOfTheArray - 1; ++i) {
        swap(&arrayNumbers[i], &arrayNumbers[lengthArrayNumbers - 1 - i]);
    }
}

void array() {
    // Задача 8

    int arrayNumbers[100];
    int separator = 0;
    int lengthArrayNumbers = arrayInput(arrayNumbers);

    printf("%s\n", "Enter m:");
    scanf("%d", &separator);

    arrayReversal(arrayNumbers, separator);
    arrayReversal(arrayNumbers, lengthArrayNumbers);
    arrayReversal(arrayNumbers, lengthArrayNumbers - separator);
    for (int i = 0; i < lengthArrayNumbers; ++i) {
        printf("%d, ", arrayNumbers[i]);
    }
}

// ********

int main(void) {

    int taskNumber = -1;

    printf("%s\n", "Enter task number:");
    scanf("%d", &taskNumber);

    if (taskNumber == 1) {
        nullElements();
    }
    if (taskNumber == 2) {
        task2Swap();
    }
    if (taskNumber == 3) {
        incompleteQuotient();
    }
    if (taskNumber == 4) {
        luckyTickets();
    }
    if (taskNumber == 5) {
        balanceOfBrackets();
    }
    if (taskNumber == 6) {
        primeNumbers();
    }
    if (taskNumber == 7) {
        substring();
    }
    if (taskNumber == 8) {
        array();
    }
}
