#ifndef GRAMMAR_H
#define GRAMMAR_H


#include <istream>
#include <vector>
#include "ProductionRule.h"

class Grammar {
public:
    Grammar(std::istream & in) {
        while (true) {
            ProductionRule rule;
            auto success = rule.read(in);
            if (!success) {
                break;
            }

            rules.push_back(rule);
        }
    }

    std::string getStartSymbol() {
        if (rules.empty()) {
            throw std::runtime_error("No production rules exist");
        }

        return rules[0].lhs;
    }

    std::vector<ProductionRule> findRulesContaining(std::string const& symbol) {
        std::vector<ProductionRule> matchesRules;

        for (auto const& rule : rules) {
            if (rule.rhs.find(symbol) != std::string::npos) {
                matchesRules.push_back(rule);
            }
        }

        return matchesRules;
    }

private:
    std::vector<ProductionRule> rules;
};


#endif //GRAMMAR_H
