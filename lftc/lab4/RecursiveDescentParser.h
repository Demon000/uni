#ifndef RECURSIVEDESCENTPARSER_H
#define RECURSIVEDESCENTPARSER_H

#include <stack>
#include <istream>

#include <unistd.h>

#include "Grammar.h"

enum ParserState {
    Q,
    R,
    T,
    E,
};

#define DEBUG 0

class RecursiveDescentParser {
public:
    RecursiveDescentParser(Grammar & grammar) : grammar(grammar) {}

    std::vector<Symbol> parseString(std::string const& input) {
        std::vector<Symbol> workStack;
        std::vector<Symbol> inputStack;
        ParserState state = ParserState::Q;
        int position = 0;

        ProductionRule startingRule = grammar.getStartProductionRule();
        inputStack.push_back(startingRule.getLhsSymbol());

        while (true) {
            if (state == ParserState::Q) {
                if (inputStack.empty()) {
                    if (DEBUG) std::cout << "input stack empty" << std::endl;

                    if (position == input.size()) {
                        state = ParserState::T;
                        if (DEBUG) std::cout << "set parser state to T" << std::endl;
                    } else {
                        return {};
                    }

                    continue;
                }

                auto symbol = inputStack.back();
                inputStack.pop_back();

                if (symbol.type == SymbolType::TERMINAL && input[position] == symbol.buffer[0]) {
                    if (DEBUG) std::cout << "found terminal " << symbol.toString() << " matching "
                                         << input[position] << " in input stack" << std::endl;

                    workStack.push_back(symbol);
                    position++;
                } else if (symbol.type == SymbolType::TERMINAL && input[position] != symbol.buffer[0]) {
                    if (DEBUG) std::cout << "found terminal " << symbol.toString() << " not matching "
                                         << input[position] << " in input stack" << std::endl;

                    inputStack.push_back(symbol);
                    state = ParserState::R;
                    if (DEBUG) std::cout << "setting parser state to R" << std::endl;
                } else if (symbol.type == SymbolType::NON_TERMINAL) {
                    if (DEBUG) std::cout << "found non terminal " << symbol.toString()
                                         << " in input stack" << std::endl;

                    workStack.push_back(symbol);

                    auto const& rule = grammar.getProductionRuleWithLhsIndex(symbol, symbol.index);
                    auto rhsSymbols = rule.getRhsSymbols();

                    while (!rhsSymbols.empty()) {
                        auto rhsSymbol = rhsSymbols.back();
                        if (DEBUG) std::cout << "add rhs symbol to input stack " << rhsSymbol.toString()
                                             << " to input stack" << std::endl;

                        rhsSymbols.pop_back();
                        inputStack.push_back(rhsSymbol);
                    }
                }
            } else if (state == ParserState::R) {
                if (workStack.empty()) {
                    if (DEBUG) std::cout << "work stack empty" << std::endl;
                    return {};
                }

                auto symbol = workStack.back();
                workStack.pop_back();

                if (symbol.type == SymbolType::TERMINAL) {
                    if (DEBUG) std::cout << "remove terminal symbol " << symbol.toString()
                                         << " from work stack and add it on input stack" << std::endl;

                    position--;
                    inputStack.push_back(symbol);
                } else if (symbol.type == SymbolType::NON_TERMINAL) {
                    if (DEBUG) std::cout << "remove non terminal symbol " << symbol.toString()
                            << " from work stack" << std::endl;

                    auto const& rule = grammar.getProductionRuleWithLhsIndex(symbol, symbol.index);
                    auto size = rule.getRhsSymbols().size();

                    while (size) {
                        auto const& rhsSymbol = inputStack.back();
                        if (DEBUG) std::cout << "remove rhs symbol " << rhsSymbol.toString()
                                             << " from input stack" << std::endl;

                        inputStack.pop_back();
                        size--;
                    }

                    try {
                        auto const& nextRule = grammar.getProductionRuleWithLhsIndex(symbol, symbol.index + 1);
                        auto const& nextSymbol = nextRule.getLhsSymbol();
                        if (DEBUG) std::cout << "add next non terminal symbol " << nextSymbol.toString()
                                             << " to input stack" << std::endl;

                        inputStack.push_back(nextSymbol);

                        if (DEBUG) std::cout << "set parser state to Q" << std::endl;
                        state = ParserState::Q;
                    } catch (std::runtime_error const& error) {
                        if (DEBUG) std::cout << "add non terminal symbol " << symbol.toString()
                                             << " back to input stack" << std::endl;

                        inputStack.push_back(symbol);

                        if (position == 0) {
                            if (DEBUG) std::cout << "set parser state to E" << std::endl;
                            state = ParserState::E;
                        }
                    }
                }
            } else if (state == ParserState::E) {
                return {};
            } else if (state == ParserState::T) {
                return workStack;
            }

            if (DEBUG) {
                std::cout << "work stack" << std::endl;
                for (auto const& symbol: workStack) {
                    std::cout << symbol.toString();
                }
                std::cout << std::endl;

                std::cout << "input stack" << std::endl;
                for (auto it = inputStack.rbegin(); it != inputStack.rend(); it++) {
                    std::cout << it->toString();
                }
                std::cout << std::endl;

                sleep(1);
            }
        }
    }

    std::vector<Symbol> parseStream(std::istream & in) {
        std::string input;
        std::getline(in, input);
        return parseString(input);
    }

private:
    Grammar & grammar;
};


#endif //RECURSIVEDESCENTPARSER_H
