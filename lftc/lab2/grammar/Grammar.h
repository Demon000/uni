#ifndef GRAMMAR_H
#define GRAMMAR_H


#include <istream>
#include <vector>
#include "ProductionRule.h"

class Grammar {
public:
    explicit Grammar(std::istream & in, bool upperCaseNonTerminals = false) {
        read(in, upperCaseNonTerminals);
    }

    Grammar() = default;

    void read(std::istream & in, bool upperCaseNonTerminals) {
        while (true) {
            if (!in) {
                break;
            }

            ProductionRule rule;
            auto success = rule.read(in, upperCaseNonTerminals);
            if (!success) {
                continue;
            }

            auto & lhsSymbol = rule.getLhsSymbol();

            lhsSymbol.index = 0;
            for (auto const& r : rules) {
                if (lhsSymbol == r.getLhsSymbol()) {
                    lhsSymbol.index++;
                }
            }

            rules.push_back(rule);
        }
    }

    [[nodiscard]] std::vector<ProductionRule> getProductionRules() const {
        return rules;
    }

    [[nodiscard]] ProductionRule getStartProductionRule() const {
        return rules[0];
    }

    ProductionRule getProductionRuleWithLhsIndex(Symbol const& lhsSymbol, int index) const {
        for (auto const& rule : rules) {
            auto const& s = rule.getLhsSymbol();
            if (s == lhsSymbol && s.index == index) {
                return rule;
            }
        }

        std::stringstream ss;
        ss << "Failed to find production rule with lhs symbol ";
        ss << lhsSymbol.buffer;
        ss << " with index ";
        ss << index;
        throw std::runtime_error(ss.str());
    }

private:
    std::vector<ProductionRule> rules;
};


#endif //GRAMMAR_H
