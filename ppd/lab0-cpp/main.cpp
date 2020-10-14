#include <iostream>
#include "PPDUtils.h"

int main() {
    PPDUtils::writeRandomNumbersToFile("text.txt", 30, 1, 10);
    int result = PPDUtils::compareNumbersFromFile("first.txt", "second.txt");
    std::cout << "first.txt vs second.txt: " << result << std::endl;
    return 0;
}
