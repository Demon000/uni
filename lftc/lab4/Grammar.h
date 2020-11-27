#ifndef GRAMMAR_H
#define GRAMMAR_H


#include <istream>
#include <vector>
#include "ProductionRule.h"

class Grammar {
public:
    explicit Grammar(std::istream & in) {
        read(in);
    }

    Grammar() = default;

    void read(std::istream & in) {
        while (true) {
            if (!in) {
                break;
            }

            ProductionRule rule;
            auto success = rule.read(in);
            if (!success) {
                continue;
            }

            rules.push_back(rule);
        }
    }

    template <typename F>
    std::vector<Symbol> getFilteredSymbols(F fn) const {
        std::vector<Symbol> symbols;
        for (auto const& rule : rules) {
            std::vector<Symbol> filteredSymbols = rule.getFilteredSymbols(fn);
            symbols.insert(symbols.end(), filteredSymbols.begin(), filteredSymbols.end());
        }
        return symbols;
    }

    [[nodiscard]] std::vector<Symbol> getTerminalSymbols() const {
        return getFilteredSymbols(Symbol::isTerminal);
    }

    [[nodiscard]] std::vector<Symbol> getNonTerminalSymbols() const {
        return getFilteredSymbols(Symbol::isNonTerminal);
    }

    [[nodiscard]] std::vector<ProductionRule> getProductionRules() const {
        return rules;
    }

    template <typename F>
    [[nodiscard]] std::vector<ProductionRule> getFilteredProductionRules(F fn) const {
        std::vector<ProductionRule> filteredRules;
        std::copy_if(rules.begin(), rules.end(), std::back_inserter(filteredRules), fn);
        return filteredRules;
    }

    std::vector<ProductionRule> getProductionRulesForSymbol(std::string const& name) const {
        return getFilteredProductionRules([&](ProductionRule const& rule) {
            return rule.isSymbolNameInLhs(name);
        });
    }

private:
    std::vector<ProductionRule> rules;
};


#endif //GRAMMAR_H
