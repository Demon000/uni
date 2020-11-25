#ifndef PRODUCTIONRULE_H
#define PRODUCTIONRULE_H


#include <istream>
#include <string>
#include <sstream>
#include <iostream>

class ProductionRule {
public:
    bool read(std::istream & in) {
        std::string *buffer = &lhs;
        bool isArrowBegin = true;
        char c;

        while (true) {
            c = in.get();
            if (!in) {
                break;
            }

            if (c == '\n') {
                break;
            }

            if (isspace(c)) {
                continue;
            }

            if (c == '-') {
                isArrowBegin = true;
                continue;
            }

            if (c == '>' && isArrowBegin) {
                isArrowBegin = false;
                buffer = &rhs;
                continue;
            }

            buffer->push_back(c);
        }

        if (lhs.empty() && rhs.empty()) {
            return false;
        }

        if (lhs.empty()) {
            throw std::runtime_error("Failed to read production rule lhs");
        }

        if (rhs.empty()) {
            throw std::runtime_error("Failed to read production rule rhs");
        }

        return true;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "ProductionRule: ";
        ss << "lhs: " << lhs << ", ";
        ss << "rhs: " << rhs << std::endl;
        return ss.str();
    }

    std::string lhs;
    std::string rhs;
};


#endif //PRODUCTIONRULE_H
