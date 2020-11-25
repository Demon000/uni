#ifndef POLYNOMIALADDER_H
#define POLYNOMIALADDER_H


#include <utility>
#include <vector>
#include <istream>

#include "Queue.h"
#include "Polynomial.h"



class PolynomialAdder {
public:
    PolynomialAdder(LockingType type) : polynomial(Polynomial(type)) {}

    void queueMember(PolynomialMember const& member) {
        memberQueue.pushBack(member);
    }

    void takeMembersAndAdd() {
        while (memberQueue.shouldWait()) {
            PolynomialMember member;
            auto taken = memberQueue.popFront(member);
            if (!taken) {
                continue;
            }

            polynomial.add(member);
        }
    }

    void finishQueueingMembers() {
        memberQueue.markClosed();
    }

    std::vector<PolynomialMember> getMembers() {
        return polynomial.getMembers();
    }

private:
    Queue<PolynomialMember> memberQueue;
    Polynomial polynomial;
};


#endif //POLYNOMIALADDER_H
