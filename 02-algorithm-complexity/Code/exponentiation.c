#include "headerFile.h"
#include <stdbool.h>
#include <stdio.h>

long double exponentiationLineTime(long long baseOfDegree, long exponent) {
    long double result = 1;
    bool negativeDegree = false;
    if (exponent < 0) {
        exponent *= -1;
        negativeDegree = true;
    }

    if (exponent == 0) {
        return result;
    }
    for (int i = 0; i < exponent; i++) {
        result *= baseOfDegree;
    }
    return negativeDegree ? (1.0 / result) : result;
}

long double exponentiationLogTime(long long baseOfDegree, long exponent) {
    long double result = 1;
    bool negativeDegree = false;
    if (exponent < 0) {
        exponent *= -1;
        negativeDegree = true;
    }

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

    return negativeDegree ? 1.0 / result : result;
}
// 9.70590147927644445685e-010
bool testForCorrectnessOfCalculation() {
    const double epsilon = 0.000001;
    bool test1LineTime = exponentiationLineTime(5, 2) == 25;
    bool test2LineTime = exponentiationLineTime(50, 10) == 97656250000000000;
    bool test3LineTime = 0.000010 - epsilon < exponentiationLineTime(10, -5);
    bool test4LineTime = 0.000010 + epsilon > exponentiationLineTime(10, -5);
    bool test5LineTime = exponentiationLineTime(-3, 3) == -27;
    bool test6LineTime = epsilon > exponentiationLineTime(1010, -3);
    bool allTestLineTime = test1LineTime && test2LineTime && test3LineTime && test4LineTime && test5LineTime && test6LineTime;

    bool test1LogTime = exponentiationLogTime(5, 2) == 25;
    bool test2LogTime = exponentiationLogTime(50, 10) == 97656250000000000;
    bool test3LogTime = 0.000010 - epsilon < exponentiationLogTime(10, -5);
    bool test4LogTime = 0.000010 + epsilon > exponentiationLogTime(10, -5);
    bool test5LogTime = exponentiationLineTime(-3, 3) == -27;
    bool test6LogTime = epsilon > exponentiationLogTime(1010, -3);
    bool allTestLogTime = test1LogTime && test2LogTime && test3LogTime && test4LogTime && test5LogTime && test6LogTime;

    return (allTestLineTime && allTestLogTime);
}

void exponentiationTask() {
    long exponent = -1;
    long long baseOfDegree = -1;

    if (!testForCorrectnessOfCalculation()) {
        printf("Tests failed\n");
        return;
    }

    printf("Enter the base of the degree:\n");
    if (scanf("%lld", &baseOfDegree) != 1) {
        printf("The base of the degree is entered incorrectly\n");
        return;
    }

    printf("Enter the exponent: ");
    if (scanf("%ld", &exponent) != 1) {
        printf("The degree was entered incorrectly\n");
        return;
    }

    long double resultExponentiationLogTime = exponentiationLogTime(baseOfDegree, exponent);
    long double resultExponentiationLineTime = exponentiationLineTime(baseOfDegree, exponent);

    if (exponent == 0 && baseOfDegree == 0) {
        printf("Zero to the power of zero is an uncertainty\n");
        return;
    }

    printf("Result for logarithm: %Lf\n", resultExponentiationLogTime);
    printf("Result for line: %Lf\n", resultExponentiationLineTime);
}