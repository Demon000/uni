#ifndef LAB3_HOME_MPI_H
#define LAB3_HOME_MPI_H

#include <fstream>

void runManual(std::istream & firstIn, std::istream & secondIn, std::ofstream & out);
void runScatterGather(std::istream & firstIn, std::istream & secondIn, std::ofstream & out);
void runIterative(std::istream & firstIn, std::istream & secondIn, std::ofstream & out);

static void readNumberAllDigits(std::istream & in, int *digits, int noDigits, int maxNoDigits) {
    for (int i = 0; i < noDigits; i++) {
        char c;
        in >> c;
        digits[i] = c - '0';
    }

    for (int i = noDigits; i < maxNoDigits; i++) {
        digits[i] = 0;
    }
}

static void readNumberDigits(std::istream & in, int *digits,
                                  int noDigitsStart, int noDigitsToRead,
                                  int noDigits, int maxNoDigits) {
    int i = 0;
    char c;

    while (i < noDigitsToRead && i + noDigitsStart < maxNoDigits) {
        if (i + noDigitsStart < noDigits) {
            in >> c;
            digits[i] = c - '0';
        } else {
            digits[i] = 0;
        }

        i++;
    }
}

static int addWithCarry(const int *firstDigits, const int *secondDigits,
                 int *resultDigits, int noDigits, int carry, bool & isAllNine) {
    int noNineDigits = 0;

    for (int i = 0; i < noDigits; i++) {
        int first_digit = firstDigits[i];
        int second_digit = secondDigits[i];
        int sum = first_digit + second_digit + carry;

        carry = sum / 10;
        resultDigits[i] = sum % 10;

        if (resultDigits[i] == 9) {
            noNineDigits++;
        }
    }

    isAllNine = noNineDigits == noDigits;

    return carry;
}

static int addCarryAllNine(int *resultDigits, int noDigits, int carry) {
    if (carry == 0) {
        return 0;
    }

    for (int i = 0; i < noDigits; i++) {
        resultDigits[i] = 0;
    }

    return 1;
}

static void addCarry(int *resultNumber, int noDigits, int carry) {
    if (carry == 0) {
        return;
    }

    for (int i = 0; i < noDigits; i++) {
        int sum = resultNumber[i] + carry;

        carry =  sum / 10;
        resultNumber[i] = sum % 10;

        if (carry == 0) {
            break;
        }
    }
}

static void printDigits(std::ostream & out, int *number, int noDigits) {
    out << noDigits << std::endl;
    for (int i = 0; i < noDigits; i++) {
        out << number[i];
    }
    out << std::endl;
}

static void printDigitsTrimZeros(std::ostream & out, int *digits, int maxNoDigits) {
    int noNonZeroDigits = 0;
    for (int i = 0; i < maxNoDigits; i++) {
        if (digits[i] != 0) {
            noNonZeroDigits = i + 1;
        }
    }

    printDigits(out, digits, noNonZeroDigits);
}

#endif //LAB3_HOME_MPI_H
