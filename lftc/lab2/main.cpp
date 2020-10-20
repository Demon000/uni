#include <iostream>
#include "Lexer.h"

int main() {
    std::ifstream in("test.c.txt");
    std::ofstream out("lexer.txt");
    Lexer lexer;

    auto status = lexer.tokenize(in);
    if (status != PARSE_SUCCESS) {
        std::cout << "Failed to parse input file\n";
        std::cout << "Buffer remaining:\n";
        std::cout << in.rdbuf();
        return -1;
    }

    lexer.describe(out);

    return 0;
}
