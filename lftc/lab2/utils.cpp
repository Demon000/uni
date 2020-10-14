#include "utils.h"

bool isValidDigit(char c, bool starting) {
    char lowest;
    if (starting) {
        lowest = '1';
    } else {
        lowest = '0';
    }

    if (c < lowest || c > '9') {
        return false;
    }

    return true;
}

bool isValidIntConstant(const std::string &buffer, size_t pos, bool checkStarting) {
    for (size_t i = pos; i < buffer.size(); i++) {
        if (!isValidDigit(buffer[i], i == pos && checkStarting)) {
            return false;
        }
    }

    return true;
}
