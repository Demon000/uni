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

    static bool isWhitespace(Symbol const& symbol) {
        return symbol.type == WHITESPACE;
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
            ss << '#';
            ss << index;
            ss << '>';
        }

        if (withDetails) {
            ss << "'";
        }

        return ss.str();
    }

    friend int operator<=>(const Symbol &first, const Symbol &second) {
        return second.type - first.type + first.buffer.compare(second.buffer);
    }

    friend bool operator==(const Symbol &first, const Symbol &second) {
        return (first <=> second) == 0;
    }

    int index = 0;
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

    [[nodiscard]] static bool isSymbolsEmpty(std::vector<Symbol> const& symbols) {
        return std::all_of(symbols.begin(), symbols.end(), [&](Symbol const& symbol) {
            return symbol.type == WHITESPACE;
        });
    }

    enum ParseState {
        NONE,
        ARROW,
        NON_TERMINAL_SYMBOL,
        NON_TERMINAL_SYMBOL_FIRST_CHAR,
        TERMINAL_SYMBOL,
        TERMINAL_SYMBOL_FIRST_CHAR,
    };

    static bool readSymbols(std::istream & in, std::vector<Symbol> & symbols, bool isLhs,
                            bool upperCaseNonTerminals) {
        enum ParseState state = NONE;
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

            auto isNonTerminalState = [](ParseState state) { return state == NON_TERMINAL_SYMBOL
                                                                    || state == NON_TERMINAL_SYMBOL_FIRST_CHAR; };

            auto isTerminalState = [](ParseState state) { return state == TERMINAL_SYMBOL
                                                                 || state == TERMINAL_SYMBOL_FIRST_CHAR; };

            if (c == '-' && state == NONE && isLhs) {
                state = ARROW;
            } else if (c == '>' && state == ARROW) {
                break;
            } else if (c == '<' && state == NONE) {
                state = NON_TERMINAL_SYMBOL_FIRST_CHAR;
            } else if (c == '[' && state == NONE) {
                state = TERMINAL_SYMBOL_FIRST_CHAR;
            } else if ((c == '>' && isNonTerminalState(state))
                    || (c == ']' && isTerminalState(state))) {
                state = NONE;
            } else if (isNonTerminalState(state)) {
                if (state == NON_TERMINAL_SYMBOL_FIRST_CHAR) {
                    state = NON_TERMINAL_SYMBOL;
                    addNewSymbol(symbols, c, NON_TERMINAL);
                } else {
                    addToSameSymbol(symbols, c, NON_TERMINAL);
                }
            } else if (isTerminalState(state)) {
                if (state == TERMINAL_SYMBOL_FIRST_CHAR) {
                    state = TERMINAL_SYMBOL;
                    addNewSymbol(symbols, c, TERMINAL);
                } else {
                    addToSameSymbol(symbols, c, TERMINAL);
                }
            } else if (upperCaseNonTerminals && c >= 'A' && c <= 'Z') {
                addNewSymbol(symbols, c, NON_TERMINAL);
            } else {
                addNewSymbol(symbols, c, TERMINAL);
            }
        }
    }

    bool read(std::istream & in, bool upperCaseNonTerminals) {
        readSymbols(in, lhsSymbols, true, upperCaseNonTerminals);
        if (isSymbolsEmpty(lhsSymbols)) {
            return false;
        }

        readSymbols(in, rhsSymbols, false, upperCaseNonTerminals);
        if (isSymbolsEmpty(rhsSymbols)) {
            throw std::runtime_error("Failed to read production rule rhs");
        }

        return true;
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
        Symbol const& lhsSymbol = getLhsSymbol();

        ss << lhsSymbol.toString() << " ";
        ss << "->";
        ss << symbolsToString(rhsSymbols, withDetails);

        return ss.str();
    }

    [[nodiscard]] Symbol const & getLhsSymbol() const {
        for (auto const& symbol : lhsSymbols) {
            if (Symbol::isNonTerminal(symbol)) {
                return symbol;
            }
        }

        throw std::runtime_error("Failed to find non terminal symbol in lhs");
    }

    [[nodiscard]] Symbol & getLhsSymbol() {
        for (auto & symbol : lhsSymbols) {
            if (Symbol::isNonTerminal(symbol)) {
                return symbol;
            }
        }

        throw std::runtime_error("Failed to find non terminal symbol in lhs");
    }

    template <typename F>
    [[nodiscard]] std::vector<Symbol> getFilteredRhsSymbols(F fn) const {
        std::vector<Symbol> symbols;
        std::copy_if(rhsSymbols.begin(), rhsSymbols.end(), std::back_inserter(symbols), fn);
        return symbols;
    }

    [[nodiscard]] std::vector<Symbol> getRhsSymbols() const {
        return getFilteredRhsSymbols([](auto const &symbol) {
            return !Symbol::isWhitespace(symbol);
        });
    }

    int getIndex() {
        return getLhsSymbol().index;
    }

    int setIndex(int index) {
        getLhsSymbol().index = index;
    }

private:
    std::vector<Symbol> lhsSymbols;
    std::vector<Symbol> rhsSymbols;
};


#endif //PRODUCTIONRULE_H
