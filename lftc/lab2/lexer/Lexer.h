#ifndef LAB2_LEXER_H
#define LAB2_LEXER_H

#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <map>
#include <memory>
#include "LexerTokens.h"
#include "../LexerTokenIds.h"
#include "LexerStatus.h"
#include "../binary_search_tree/BinarySearchTree.h"
#include "../finite_state_machine/FiniteStateMachine.h"

class Lexer {
public:
    Lexer(std::vector<std::shared_ptr<Token>> tokenDefinitions)
        : tokenDefinitions(std::move(tokenDefinitions)) {}
    LexerStatus tokenize(std::istream& in);
    void describe(std::ostream& out);
    std::vector<Token> getTokens();
private:
    void insertToken(const std::shared_ptr<Token>& token);
    void insertIndexedToken(const std::shared_ptr<Token>& token);
    void insertSimpleToken(const std::shared_ptr<Token>& token);
    void describeTokens(std::ostream &out);
    void describeIndexedTokenValues(const std::vector<IndexedTokenValue> &values, std::ostream &out);

    std::vector<std::shared_ptr<Token>> tokens;
    BinarySearchTree<IndexedTokenValue> identifiers;
    BinarySearchTree<IndexedTokenValue> constants;
    std::vector<std::shared_ptr<Token>> tokenDefinitions;
};


#endif //LAB2_LEXER_H
