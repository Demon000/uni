#ifndef POLYNOMIALSTREAM_H
#define POLYNOMIALSTREAM_H

#include <istream>

#include "Polynomial.h"

class PolynomialStream {
public:
    PolynomialStream() : PolynomialStream(nullptr) {}

    PolynomialStream(std::istream *in) : in(in) {}

    /**
     * Read from a stream with polynomial members, run a function for each member constructed
     * @tparam F function template
     * @param fn function to run
     */
    template <typename F>
    void read(F fn) const {
        while (true) {
            int coefficient;
            int power;

            *in >> coefficient;
            if (!*in) {
                break;
            }

            *in >> power;
            if (!*in) {
                throw std::runtime_error("Failed to read power");
            }

            auto member = PolynomialMember(coefficient, power);
            fn(member);
        }
    }

    std::istream *in;
};


#endif //POLYNOMIALSTREAM_H
