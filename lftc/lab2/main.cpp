#include <iostream>
#include "Lexer.h"
#include "FiniteStateMachine.h"

void runUserInput() {
    FiniteStateMachine fsm;

    while (true) {
        std::cout <<
                  "1. Read from file\n"
                  "2. Read from stdin\n"
                  "3. Print states\n"
                  "4. Print alphabet\n"
                  "5. Print transitions\n"
                  "6. Print final states\n"
                  "7. Parse\n"
                  "0. Exit\n"
                ;

        int key;

        std::cout << "Command: ";
        std::cin >> key;

        if (key == 0) {
            break;
        } else if (key == 1) {
            std::string filename;
            std::cout << "File name: ";
            std::cin >> filename;

            std::ifstream in(filename);
            fsm.read(in);
        } else if (key == 2) {
            fsm.read(std::cin);
        } else if (key == 3) {
            std::cout << fsm.statesToString();
        } else if (key == 4) {
            std::cout << "Alphabet -> " << fsm.getAlphabet() << std::endl;
        } else if (key == 5) {
            std::cout << fsm.transitionsToString();
        } else if (key == 6) {
            std::cout << fsm.finalStatesToString();
        } else if (key == 7) {
            std::cout << "Text to parse: ";

            std::string text;
            std::cin >> text;

            auto result = fsm.parse(text);
            std::cout << result.toString();
        } else {
            std::cout << "Invalid command.\n";
        }
    }
}

void runLexer() {
    std::ifstream in("test.c.txt");
    std::ofstream out("lexer.csv");
    Lexer lexer;

    auto status = lexer.tokenize(in);
    if (status != PARSE_SUCCESS) {
        std::cout << "Failed to parse input file\n";
        std::cout << "Buffer remaining:\n";
        std::cout << in.rdbuf();
    }

    lexer.describe(out);
}

void testFSM() {
    FiniteStateMachine fsm("fsm_catch_all_keywords.txt");
    std::cout << fsm.statesToString();
    std::cout << fsm.transitionsToString();
    std::cout << fsm.finalStatesToString();

    auto result = fsm.parse("aabbbcd_321421s???");
    std::cout << result.toString();
}

int main() {
    runLexer();
//    runUserInput();
//    testFSM();

    return 0;
}
