#include <iostream>
#include <fstream>
#include "Grammar.h"

void printSymbols(std::vector<Symbol> const& symbols) {
    for (auto const& symbol : symbols) {
        std::cout << symbol.toString() << std::endl;
    }
    std::cout << std::endl;
}

void printProductionRules(std::vector<ProductionRule> const& rules, bool withDetails) {
    for (auto const& rule : rules) {
        std::cout << rule.toString(withDetails) << std::endl;
    }
}

bool takeUserInput(Grammar const& grammar) {
    std::cout <<
              "1. Print non-terminals\n"
              "2. Print terminals\n"
              "3. Print production rules\n"
              "4. Print production rules with details\n"
              "5. Print production rules for terminal symbol\n"
              "6. Print production rules for terminal symbol with details\n"
              "0. Exit\n";

    int option;
    std::cout << "Option: ";
    std::cin >> option;

    switch (option) {
        case 1: {
            auto symbols = grammar.getNonTerminalSymbols();
            printSymbols(symbols);
        } break;
        case 2: {
            auto symbols = grammar.getTerminalSymbols();
            printSymbols(symbols);
        } break;
        case 3: {
            auto productionRules = grammar.getProductionRules();
            printProductionRules(productionRules, false);
        } break;
        case 4: {
            auto productionRules = grammar.getProductionRules();
            printProductionRules(productionRules, true);
        } break;
        case 5: {
            std::cout << "Symbol name: ";
            std::string name;
            std::cin >> name;
            auto productionRules = grammar.getProductionRulesForTerminalSymbol(name);
            printProductionRules(productionRules, false);
        } break;
        case 6: {
            std::cout << "Symbol name: ";
            std::string name;
            std::cin >> name;
            auto productionRules = grammar.getProductionRulesForTerminalSymbol(name);
            printProductionRules(productionRules, true);
        } break;
        case 0:
            return false;
    }

    return true;
}

int main() {
//    std::ifstream in("input.txt");
//    Grammar grammar{in, false};
    std::ifstream in("input_simple.txt");
    Grammar grammar{in, true};
    while (takeUserInput(grammar)) {}

    return 0;
}
