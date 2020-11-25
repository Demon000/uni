#include <iostream>
#include <fstream>
#include "Grammar.h"

int main() {
    std::ifstream in("input.txt");
    Grammar grammar{in};
    std::string symbol = grammar.getStartSymbol();
    std::vector<ProductionRule> rules = grammar.findRulesContaining(symbol);

    for (auto const& rule : rules) {
        std::cout << rule.toString();
    }

    return 0;
}
