#include <istream>
#include <iostream>
#include "addition.h"

void runIterative(std::istream & firstIn, std::istream & secondIn, std::ofstream & out) {
    int firstNoDigits;
    int secondNoDigits;

    firstIn >> firstNoDigits;
    if (!firstIn) {
        throw std::runtime_error("Failed to open file");
    }

    secondIn >> secondNoDigits;
    if (!firstIn) {
        throw std::runtime_error("Failed to open file");
    }

    int maxNoDigits = std::max(firstNoDigits, secondNoDigits) + 1;
    int *firstDigits = new int[maxNoDigits];
    int *secondDigits = new int[maxNoDigits];
    int *resultDigits = new int[maxNoDigits];

    readNumberAllDigits(firstIn, firstDigits, firstNoDigits, maxNoDigits);
    readNumberAllDigits(secondIn, secondDigits, secondNoDigits, maxNoDigits);

    bool isAllNine;
    addWithCarry(firstDigits, secondDigits,
                             resultDigits, maxNoDigits,
                             0, isAllNine);

    printDigitsTrimZeros(out, resultDigits, maxNoDigits);
}
