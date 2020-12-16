#include <iostream>
#include <fstream>
#include "Grammar.h"
#include "RecursiveDescentParser.h"

void printProductionRules(std::vector<ProductionRule> const& rules, bool withDetails) {
    for (auto const& rule : rules) {
        std::cout << rule.toString(withDetails) << std::endl;
    }
}

void main_parser() {
    std::ifstream grammarIn("grammar_simple.txt");
    std::ifstream in{"input_simple.txt"};

    Grammar grammar{grammarIn, true};
    RecursiveDescentParser parser{grammar};

    auto productionRules = grammar.getProductionRules();
    printProductionRules(productionRules, false);

    auto workStack = parser.parseStream(in);
    for (auto const& symbol : workStack) {
        std::cout << symbol.toString();
    }
}

int main() {
    main_parser();
}
