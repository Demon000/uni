#include <iostream>
#include "Lexer.h"

int main() {
    std::ifstream in("test.c.txt");
    std::ofstream out("lexer.txt");
    Lexer lexer;

    lexer.tokenize(in);
    lexer.describe(out);

    return 0;
}
