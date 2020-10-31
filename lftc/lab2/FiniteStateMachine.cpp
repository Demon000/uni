#include "FiniteStateMachine.h"
#include "StreamUtils.h"

std::shared_ptr<FiniteStateMachine::State> FiniteStateMachine::readState(std::istream &in) {
    auto state = std::make_shared<State>();
    bool readSuccess;

    readSuccess = StreamUtils::readUntilDelimiter(in, state->name);
    if (!readSuccess) {
        throw std::runtime_error("Failed to read state name");
    }

    while (in) {
        std::string option;
        readSuccess = StreamUtils::readUntilDelimiter(in, option);
        if (!readSuccess) {
            break;
        }

        if (option == "f") {
            state->isFinal = true;
        }
    }

    return state;
}

std::shared_ptr<FiniteStateMachine::Transition> FiniteStateMachine::readTransition(std::istream &in) {
    auto transition = std::make_shared<Transition>();
    bool readSuccess;
    std::string name;

    readSuccess = StreamUtils::readUntilDelimiter(in, name);
    if (!readSuccess) {
        throw std::runtime_error("Failed to read transition from state name");
    }
    transition->from = findState(name);

    readSuccess = StreamUtils::readUntilDelimiter(in, name);
    if (!readSuccess) {
        throw std::runtime_error("Failed to read transition to state name");
    }
    transition->to = findState(name);

    std::string characters;

    readSuccess = StreamUtils::readUntilDelimiter(in, characters);
    if (!readSuccess) {
        throw std::runtime_error("Failed to read transition characters");
    }

    std::stringstream charactersStream{characters};

    bool isEscapedChar = false;
    bool isRangeEnd = false;
    while (charactersStream) {
        unsigned char c = charactersStream.get();
        if (charactersStream.fail()) {
            break;
        }

        if (c == '\\' && !isEscapedChar) {
            isEscapedChar = true;
            continue;
        }

        if (c == '-' && !isEscapedChar) {
            isRangeEnd = true;
            continue;
        }

        isEscapedChar = false;

        unsigned char rangeStart;
        if (isRangeEnd) {
            if (transition->characters.empty()) {
                throw std::runtime_error("Range sequence has no start");
            }

            rangeStart = transition->characters.back();
        } else {
            rangeStart = c;
        }

        isRangeEnd = false;

        for (unsigned char i = rangeStart; i <= c; i++) {
            transition->characters.push_back(i);
        }
    }

    if (isEscapedChar) {
        throw std::runtime_error("Unterminated escape sequence");
    }

    if (isRangeEnd) {
        throw std::runtime_error("Unterminated range sequence");
    }

    return transition;
}

void FiniteStateMachine::read(std::istream &in) {
    states.clear();
    transitions.clear();
    nameStateMap.clear();

    while (in) {
        bool readSuccess;
        std::string line;

        readSuccess = StreamUtils::readLine(in, line);
        if (!readSuccess) {
            break;
        }

        if (line.empty()) {
            continue;
        }

        std::stringstream lineStream{line};
        std::string type;

        readSuccess = StreamUtils::readUntilDelimiter(lineStream, type);
        if (!readSuccess) {
            throw std::runtime_error("Failed to read element type");
        }

        if (type == "s") {
            auto state = readState(lineStream);
            states.push_back(state);
            nameStateMap.insert(std::make_pair(state->name, state));
        } else if (type == "t") {
            auto transition = readTransition(lineStream);
            transitions.push_back(transition);
            transition->from->transitions.push_back(transition);
        } else {
            std::stringstream ss;
            ss << "Unrecognized element type " << "\"" << type << "\"" << std::endl;
            throw std::runtime_error(ss.str());
        }
    }
}

std::shared_ptr<FiniteStateMachine::State> FiniteStateMachine::findState(std::string const& name) const {
    auto it = nameStateMap.find(name);
    if (it == nameStateMap.end()) {
        std::stringstream ss;
        ss << "Failed to find state with name " << "\"" << name << "\"";
        throw std::runtime_error(ss.str());
    }

    return it->second;
}

FiniteStateMachine::Result FiniteStateMachine::parse(std::istream &in) const {
    std::string matched;
    Result result;

    if (states.empty()) {
        throw std::runtime_error("Finite state machine has no states");
    }

    if (transitions.empty()) {
        throw std::runtime_error("Finite state machine has no transitions");
    }

    std::shared_ptr<State> currentState{nullptr};
    std::shared_ptr<State> nextState{nullptr};
    while (in) {
        if (!currentState) {
            currentState = states.at(0);
        }

        if (currentState->isFinal) {
            result.matched = matched;
        }

        unsigned char c = in.get();
        if (in.fail()) {
            break;
        }

        nextState = currentState->findNextState(c);
        if (nextState == nullptr) {
            in.putback(c);
            break;
        }

        matched.push_back(c);

        currentState = nextState;
    }

    result.matches = currentState->isFinal;

    return result;
}

FiniteStateMachine::Result FiniteStateMachine::parse(std::string const& input) const {
    std::stringstream ss{input};
    auto result = parse(ss);
    result.remaining = ss.str().substr(result.matched.length());
    return result;
}

std::string FiniteStateMachine::statesToString(std::vector<std::shared_ptr<State>> const& s) const {
    std::stringstream ss;
    for (auto const& state : s) {
        ss << state->toString();
    }
    return ss.str();
}

std::string FiniteStateMachine::statesToString() const {
    return statesToString(states);
}

std::string FiniteStateMachine::finalStatesToString() const {
    std::vector<std::shared_ptr<State>> finalStates;

    for (auto const& state : states) {
        if (state->isFinal) {
            finalStates.push_back(state);
        }
    }

    return statesToString(finalStates);
}

std::string FiniteStateMachine::getAlphabet() const {
    std::set<unsigned char> alphabet;

    for (auto const& transition : transitions) {
        for (auto const& c : transition->characters) {
            alphabet.insert(c);
        }
    }

    std::stringstream ss;

    for (auto const& character : alphabet) {
        ss << character;
    }

    return ss.str();
}

std::string FiniteStateMachine::transitionsToString() const {
    std::stringstream ss;

    for (auto const& transition : transitions) {
        ss << transition->toString();
    }

    return ss.str();
}
