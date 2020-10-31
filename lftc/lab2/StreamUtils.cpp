#include <istream>
#include "StreamUtils.h"

bool StreamUtils::skipWhitespace(std::istream &in) {
    while (in) {
        unsigned char c = in.get();
        if (in.fail()) {
            return false;
        }

        if (!isspace(c)) {
            in.putback(c);
            break;
        }
    }

    return true;
}

bool StreamUtils::read(std::istream &in, std::string &buffer, size_t size) {
    buffer.clear();

    while (true) {
        unsigned char c = in.get();
        if (in.fail()) {
            return false;
        }

        buffer.push_back(c);

        if (buffer.size() == size) {
            return true;
        }
    }
}

bool StreamUtils::readLine(std::istream &in, std::string &buffer) {
    bool foundAny = false;
    buffer.clear();

    while (in) {
        unsigned char c = in.get();
        if (in.fail()) {
            break;
        }

        foundAny = true;

        if (c == '\n') {
            break;
        }

        buffer.push_back(c);
    }

    return foundAny;
}

bool StreamUtils::readUntilDelimiter(std::istream &in, std::string &buffer, unsigned char delimiter, unsigned char escaper) {
    buffer.clear();

    bool isEscapedChar = false;
    while (in) {
        unsigned char c = in.get();
        if (in.fail()) {
            break;
        }

        if (c == escaper && !isEscapedChar) {
            isEscapedChar = true;
            continue;
        }

        if (c == delimiter && !isEscapedChar) {
            break;
        }

        isEscapedChar = false;

        buffer.push_back(c);
    }

    if (isEscapedChar) {
        throw std::runtime_error("Unterminated escape sequence");
    }

    return !buffer.empty();
}
