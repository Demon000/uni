#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H


#include <iostream>
#include <sstream>

enum LockingType {
    NO_LOCK,
    GLOBAL_LOCK,
    INDIVIDUAL_LOCK,
};

class PolynomialMember {
public:
    PolynomialMember() : coefficient(0), power(0) {}

    PolynomialMember(int coefficient, int power)
            : coefficient(coefficient), power(power) {}

    int coefficient;
    int power;
};

class Node {
public:
    Node() {}

    Node(PolynomialMember const& data) : data(data) {}

    PolynomialMember data;
    Node *next = nullptr;
    std::mutex m;
};

class Polynomial {
public:
    Polynomial(LockingType type)
            : type(type) {
    }

    /**
     * Add a polynomial member to the linked list
     * @param member the member to add
     */
    void add(PolynomialMember const& member) {
        Node *node;

        if (type == GLOBAL_LOCK) m.lock();

        /*
         * We iterate with a node behind so we can insert a new node if needed.
         */
        node = sentinel;
        if (type == INDIVIDUAL_LOCK) node->m.lock();
        while (true) {
            /*
             * There is no node after the current one, add one.
             */
            if (node->next == nullptr) {
                node->next = new Node(member);
                if (type == GLOBAL_LOCK) m.unlock();
                if (type == INDIVIDUAL_LOCK) node->m.unlock();
                return;
            }

            /*
             * The node after the current one has a smaller power than our member,
             * add a new node between the current node and the next node.
             */
            if (node->next->data.power < member.power) {
                auto *newNext = new Node(member);
                newNext->next = node->next;
                node->next = newNext;
                if (type == GLOBAL_LOCK) m.unlock();
                if (type == INDIVIDUAL_LOCK) node->m.unlock();
                return;
            }

            /*
             * The node after the current one has the same power as our member,
             * add the coefficients together.
             */
            if (node->next->data.power == member.power) {
                node->next->data.coefficient += member.coefficient;
                if (type == GLOBAL_LOCK) m.unlock();
                if (type == INDIVIDUAL_LOCK) node->m.unlock();
                return;
            }

            auto oldNode = node;
            node = node->next;
            if (type == INDIVIDUAL_LOCK) node->m.lock();
            if (type == INDIVIDUAL_LOCK) oldNode->m.unlock();
        }
    }

    /**
     * Get all the members from the polynomial
     * @return the members of the polynomial
     */
    std::vector<PolynomialMember> getMembers() {
        std::vector<PolynomialMember> members;

        m.lock();

        Node* node = sentinel->next;
        while (node != nullptr) {
            members.push_back(node->data);
            node = node->next;
        }

        m.unlock();

        return members;
    }

    void printMembers(std::ostream & out) {
        auto members = getMembers();
        bool isFirst = true;

        for (auto const& member : members) {
            if (member.coefficient > 0) {
                if (!isFirst) {
                    out << " + ";
                }
            } else {
                if (isFirst) {
                    out << "-";
                } else {
                    out << " - ";
                }
            }

            isFirst = false;

            int coefficient = std::abs(member.coefficient);
            out << coefficient << "x^" << member.power;
        }

        out << std::endl;
    }

    ~Polynomial() {
        Node* node = sentinel;

        while (node != nullptr) {
            Node* nextNode = node->next;
            delete node;
            node = nextNode;
        }
    }

private:
    LockingType type;
    Node *sentinel = new Node();
    std::mutex m;
};


#endif //POLYNOMIAL_H
