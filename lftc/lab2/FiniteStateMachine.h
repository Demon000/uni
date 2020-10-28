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

class FiniteStateMachine {
public:
    class Result {
    public:
        std::string toString() {
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

        std::shared_ptr<State> findNextState(char c) {
            for (auto const& transition : transitions) {
                if (transition->matches(c)) {
                    return transition->to;
                }
            }

            return nullptr;
        }

        std::string toString() {
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
        Transition(std::shared_ptr<State> from, std::shared_ptr<State> to, char character)
                : from(std::move(from)), to(std::move(to)), character(character) {}

        bool matches(char c) const {
            return character == c;
        }

        std::string toString() {
            std::stringstream ss;
            ss << "Transition -> "
                    << "from: " << from->name
                    << ", to: " << to->name
                    << ", character: " << character
                    << std::endl;
            return ss.str();
        }

        std::shared_ptr<State> from;
        std::shared_ptr<State> to;
        char character;
    };

    FiniteStateMachine() {}

    FiniteStateMachine(std::istream &in) {
        readFromStream(in);
    }

    template <typename T>
    void readFromStream(std::istream &in, T &value, std::string const& fail) {
        in >> value;
        if (!in) {
            throw std::runtime_error(fail);
        }
    }

    void readFromStream(std::istream &in) {
        states.clear();
        transitions.clear();
        nameStateMap.clear();

        int noStates;
        readFromStream(in, noStates, "Failed to read number of states");
        while (noStates) {
            std::string name;
            readFromStream(in, name, "Failed to read name of state");

            auto state = std::make_shared<State>(name);
            states.push_back(state);
            nameStateMap.insert(std::make_pair(name, state));

            noStates--;
        }

        int noFinalStates;
        readFromStream(in, noFinalStates, "Failed to read number of final states");
        while (noFinalStates) {
            std::string name;
            readFromStream(in, name, "Failed to read name of final state");

            auto state = findStateByName(name);
            state->isFinal = true;

            noFinalStates--;
        }

        int noTransitions;
        readFromStream(in, noTransitions, "Failed to read number of transitions");
        while (noTransitions) {
            std::string fromName, toName;
            readFromStream(in, fromName, "Failed to read from state name of transition");
            readFromStream(in, toName, "Failed to read to state name of transition");

            char c;
            readFromStream(in, c, "Failed to read character of transition");

            auto fromState = findStateByName(fromName);
            auto toState = findStateByName(toName);
            auto transition = std::make_shared<Transition>(fromState, toState, c);

            fromState->transitions.push_back(transition);
            transitions.push_back(transition);

            noTransitions--;
        }
    }

    std::shared_ptr<State> findStateByName(std::string const& name) {
        auto it = nameStateMap.find(name);
        if (it == nameStateMap.end()) {
            std::stringstream ss;

            ss << "Failed to find state with name";
            ss << "\"" << name << "\"";

            throw std::runtime_error(ss.str());
        }

        return it->second;
    }

    Result parse(std::string const& input) {
        std::string remaining{input};
        std::string matched;
        Result result {
                .remaining = remaining,
        };

        std::shared_ptr<State> currentState{nullptr};
        std::shared_ptr<State> nextState{nullptr};
        while (true) {
            if (!currentState) {
                currentState = states.at(0);
            }

            if (currentState->isFinal) {
                result.matched = matched;
                result.remaining = remaining;
            }

            if (!remaining.length()) {
                result.matches = currentState->isFinal;
                break;
            }

            nextState = currentState->findNextState(remaining.front());
            if (nextState == nullptr) {
                break;
            }

            matched.push_back(remaining.front());
            remaining.erase(0, 1);

            currentState = nextState;
        }

        return result;
    }

    std::string getStatesText(std::vector<std::shared_ptr<State>> const& s) {
        std::stringstream ss;
        for (auto const& state : s) {
            ss << state->toString();
        }
        return ss.str();
    }

    std::string getStatesText() {
        return getStatesText(states);
    }

    std::string getFinalStatesText() {
        std::vector<std::shared_ptr<State>> finalStates;

        for (auto const& state : states) {
            if (state->isFinal) {
                finalStates.push_back(state);
            }
        }

        return getStatesText(finalStates);
    }

    std::string getAlphabet() {
        std::set<char> alphabet;

        for (auto const& transition : transitions) {
            alphabet.insert(transition->character);
        }

        std::stringstream ss;

        for (auto const& character : alphabet) {
            ss << character;
        }

        return ss.str();
    }

    std::string getTransitionsText() {
        std::stringstream ss;

        for (auto const& transition : transitions) {
            ss << transition->toString();
        }

        return ss.str();
    }

private:
    std::vector<std::shared_ptr<State>> states;
    std::vector<std::shared_ptr<Transition>> transitions;
    std::map<std::string, std::shared_ptr<State>> nameStateMap;
};

#endif //LAB2_FINITESTATEMACHINE_H
