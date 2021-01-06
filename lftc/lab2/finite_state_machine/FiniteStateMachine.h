#ifndef LAB2_FINITESTATEMACHINE_H
#define LAB2_FINITESTATEMACHINE_H

#include <string>
#include <memory>
#include <utility>
#include <vector>
#include <map>
#include <istream>
#include <iostream>
#include <sstream>
#include <set>
#include <fstream>

class FiniteStateMachine {
public:
    class Result {
    public:
        std::string toString() const {
            std::stringstream ss;

            ss << "Result -> "
                    << "matches: " << (matches ? "true" : "false")
                    << ", matched text: " << matched
                    << ", remaining text: " << remaining
                    << std::endl;

            return ss.str();
        }

        std::string matched;
        std::string remaining;
        bool matches = false;
    };

    class Transition;

    class State {
    public:
        State(std::string name) : name(std::move(name)) {}
        State() = default;

        std::shared_ptr<State> findNextState(unsigned char c) const {
            for (auto const& transition : transitions) {
                if (transition->matches(c)) {
                    return transition->to;
                }
            }

            return nullptr;
        }

        std::string toString() const {
            std::stringstream ss;
            ss << "State -> "
                    << "name: " << name
                    << std::endl;
            return ss.str();
        }

        std::string name;
        std::vector<std::shared_ptr<Transition>> transitions;
        bool isFinal;
    };

    class Transition {
    public:
        Transition(std::shared_ptr<State> from, std::shared_ptr<State> to, unsigned char character)
                : from(std::move(from)), to(std::move(to)), characters(std::vector<unsigned char> {character}) {}
        Transition() = default;

        bool matches(unsigned char c) const {
            return std::find(characters.begin(), characters.end(), c) != characters.end();
        }

        std::string toString() const {
            std::stringstream ss;

            ss << "Transition -> "
                    << "from: " << from->name
                    << ", to: " << to->name
                    << ", characters: ";

            for (auto const& c : characters) {
                ss << c;
            }

            ss << std::endl;

            return ss.str();
        }

        std::shared_ptr<State> from;
        std::shared_ptr<State> to;
        std::vector<unsigned char> characters;
    };

    FiniteStateMachine() = default;

    FiniteStateMachine(std::istream &in) {
        read(in);
    }

    FiniteStateMachine(std::string const& filename) {
        std::ifstream in(filename);
        read(in);
    }

    void read(std::istream &in);
    Result parse(std::string const& input) const;
    Result parse(std::istream &in) const;
    std::string statesToString(std::vector<std::shared_ptr<State>> const& s) const;
    std::string statesToString() const;
    std::string finalStatesToString() const;
    std::string transitionsToString() const;
    std::string getAlphabet() const;

private:
    std::shared_ptr<State> findState(std::string const& name) const;
    std::shared_ptr<State> readState(std::istream &in);
    std::shared_ptr<Transition> readTransition(std::istream &in);

    std::vector<std::shared_ptr<State>> states;
    std::vector<std::shared_ptr<Transition>> transitions;
    std::map<std::string, std::shared_ptr<State>> nameStateMap;
};

#endif //LAB2_FINITESTATEMACHINE_H
