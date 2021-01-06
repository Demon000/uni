#ifndef LAB2_STREAMUTILS_H
#define LAB2_STREAMUTILS_H

class StreamUtils {
public:
    static bool skipWhitespace(std::istream &in);
    static bool read(std::istream &in, std::string &buffer, size_t size);
    static bool readUntilDelimiter(std::istream &in, std::string &buffer, unsigned char delimiter=',', unsigned char escaper='\\');
    static bool readLine(std::istream &in, std::string &buffer);
};

#endif //LAB2_STREAMUTILS_H
