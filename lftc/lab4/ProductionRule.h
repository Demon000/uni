#ifndef PRODUCTIONRULE_H
#define PRODUCTIONRULE_H


#include <istream>
#include <string>
#include <sstream>
#include <iostream>

enum SymbolType {
    WHITESPACE,
    TERMINAL,
    NON_TERMINAL,
};

class Symbol {
public:
    Symbol(SymbolType type, char c) : type(type) {
        buffer.push_back(c);
    }

    static bool isTerminal(Symbol const& symbol) {
        return symbol.type == TERMINAL;
    }

    static bool isNonTerminal(Symbol const& symbol) {
        return symbol.type == NON_TERMINAL;
    }

    [[nodiscard]] std::string toString(bool withDetails=false) const {
        std::stringstream ss;

        if (withDetails) {
            switch (type) {
                case WHITESPACE:
                    ss << 'w';
                    break;
                case TERMINAL:
                    ss << 't';
                    break;
                case NON_TERMINAL:
                    ss << 'n';
                    break;
            }

            ss << '`';
        }

        if (type == NON_TERMINAL) {
            ss << '<';
        }

        ss << buffer;

        if (type == NON_TERMINAL) {
            ss << '>';
        }

        if (withDetails) {
            ss << '`';
        }

        return ss.str();
    }

    SymbolType type;
    std::string buffer;
};

class ProductionRule {
public:
    static void addToSameSymbol(std::vector<Symbol> & symbols, char c, SymbolType type) {
        if (symbols.empty()) {
            addNewSymbol(symbols, c, type);
        } else {
            Symbol & symbol = symbols.back();
            if (symbol.type == type) {
                symbol.buffer.push_back(c);
            } else {
                addNewSymbol(symbols, c, type);
            }
        }
    }

    static void addNewSymbol(std::vector<Symbol> & symbols, char c, SymbolType type) {
        symbols.emplace_back(type, c);
    }

    [[nodiscard]] static bool isSymbolNameInSymbols(std::vector<Symbol> const& symbols, std::string const& name) {
        return std::any_of(symbols.begin(), symbols.end(), [&](Symbol const& symbol) {
            return symbol.type == NON_TERMINAL && symbol.buffer == name;
        });
    }

    [[nodiscard]] static bool isSymbolsEmpty(std::vector<Symbol> const& symbols) {
        return std::all_of(symbols.begin(), symbols.end(), [&](Symbol const& symbol) {
            return symbol.type == WHITESPACE;
        });
    }

    [[nodiscard]] bool isSymbolNameInLhs(std::string const& name) const {
        return isSymbolNameInSymbols(lhsSymbols, name);
    }

    static bool readSymbols(std::istream & in, std::vector<Symbol> & symbols, bool isLhs) {
        bool isEscaped = false;
        bool wasArrowBegin = false;
        bool isNonTerminalSymbol = false;
        char c;

        while (true) {
            c = in.get();

            if (!in || c == '\n') {
                break;
            }

            if (isspace(c)) {
                addToSameSymbol(symbols, c, WHITESPACE);
                continue;
            }

            if (c == '\\') {
                isEscaped = true;
                continue;
            }

            if (c == '-' && !wasArrowBegin && isLhs && !isEscaped) {
                wasArrowBegin = true;
                continue;
            }

            if (c == '>' && wasArrowBegin) {
                break;
            }

            if (c == '<' && !isNonTerminalSymbol && !isEscaped) {
                isNonTerminalSymbol = true;
                continue;
            }

            if (c == '>' && isNonTerminalSymbol && !isEscaped) {
                isNonTerminalSymbol = false;
                continue;
            }

            if (isNonTerminalSymbol) {
                addToSameSymbol(symbols, c, NON_TERMINAL);
                continue;
            }

            addToSameSymbol(symbols, c, TERMINAL);
        }
    }

    bool read(std::istream & in) {
        readSymbols(in, lhsSymbols, true);
        if (isSymbolsEmpty(lhsSymbols)) {
            return false;
        }

        readSymbols(in, rhsSymbols, false);
        if (isSymbolsEmpty(rhsSymbols)) {
            throw std::runtime_error("Failed to read production rule rhs");
        }

        return true;
    }

    template <typename F>
    std::vector<Symbol> getFilteredSymbols(F fn) const {
        std::vector<Symbol> symbols;
        std::copy_if(rhsSymbols.begin(), rhsSymbols.end(), std::back_inserter(symbols), fn);
        return symbols;
    }

    [[nodiscard]] static std::string symbolsToString(std::vector<Symbol> const& symbols, bool withDetails=false) {
        std::stringstream ss;

        for (auto const& symbol : symbols) {
            ss << symbol.toString(withDetails);
        }

        return ss.str();
    }

    [[nodiscard]] std::string toString(bool withDetails=false) const {
        std::stringstream ss;

        ss << symbolsToString(lhsSymbols, withDetails);
        ss << "->";
        ss << symbolsToString(rhsSymbols, withDetails);

        return ss.str();
    }

    std::vector<Symbol> lhsSymbols;
    std::vector<Symbol> rhsSymbols;
};


#endif //PRODUCTIONRULE_H
