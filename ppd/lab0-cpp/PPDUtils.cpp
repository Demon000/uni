#include <fstream>
#include <random>
#include <iostream>
#include "PPDUtils.h"

void PPDUtils::writeRandomNumbersToFile(const std::string& path, size_t size, int min, int max) {
    std::ofstream output(path);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max - 1);

    for(size_t i = 0 ; i < size; i++) {
        output << dist(mt) << '\n';
    }
}

int PPDUtils::compareNumbersFromFile(const std::string& first, const std::string& second) {
    std::ifstream firstInput(first);
    std::ifstream secondInput(second);
    double firstValue;
    double secondValue;

    while (!firstInput.eof()) {
        if (secondInput.eof()) {
            return -1;
        }

        firstInput >> firstValue;
        secondInput >> secondValue;

        if (firstValue < secondValue) {
            return -1;
        } else if (firstValue > secondValue) {
            return 1;
        }
    }

    if (!secondInput.eof()) {
        return -1;
    }

    return 0;
}
