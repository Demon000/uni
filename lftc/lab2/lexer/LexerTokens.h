#include "../LexerTokenIds.h"
#include "LexerStatus.h"
#include "../finite_state_machine/FiniteStateMachine.h"

#ifndef LEXERTOKENS_H
#define LEXERTOKENS_H

class Token {
public:
    Token(int id, std::string label, bool isIndexed=false)
            : id(id), label(std::move(label)), isIndexed_(isIndexed) {}
    Token() : Token(TK_DEFAULT, "") {}

    virtual LexerStatus tryFind(std::istream& in);
    bool isIndexed() const { return isIndexed_; };

    bool isIndexed_;
    int id;
    int index = 0;
    std::string buffer;
    std::string label;
};

class TextToken : public Token {
public:
    TextToken(int id, std::string label, std::string textMatch)
            : Token(id, std::move(label)), textMatch(std::move(textMatch)) {
    }
protected:
    std::string textMatch;
};

class ExactTextToken : public TextToken {
public:
    using TextToken::TextToken;
    LexerStatus tryFind(std::istream& in) override;
};

class ExactKeywordToken : public TextToken {
public:
    using TextToken::TextToken;
    LexerStatus tryFind(std::istream& in) override;

    FiniteStateMachine keywordCatchAllFsm{"fsm_catch_all.txt"};
};

class IndexedTokenValue {
public:
    IndexedTokenValue(std::string  buffer)
            : buffer(std::move(buffer)) {}

    IndexedTokenValue() {}

    friend int operator<=>(const IndexedTokenValue &lhs, const IndexedTokenValue &rhs) {
        return lhs.buffer.compare(rhs.buffer);
    }

    friend bool operator==(const IndexedTokenValue &lhs, const IndexedTokenValue &rhs) {
        return (lhs <=> rhs) == 0;
    }

    int index = 0;
    std::string buffer;
};

class DelimitedTextToken : public Token {
public:
    DelimitedTextToken(int id, std::string label, std::string start, std::string end)
            : Token(id, std::move(label), true), start(std::move(start)), end(std::move(end)) {
    }

    LexerStatus tryFind(std::istream& in) override;

private:
    std::string start;
    std::string end;
};

class IntToken : public Token {
public:
    IntToken(int id, std::string label)
            : Token(id, std::move(label), true) {}
    LexerStatus tryFind(std::istream& in) override;

    FiniteStateMachine keywordCatchAllFsm{"fsm_catch_all.txt"};
    FiniteStateMachine integerFsm{"fsm_integer.txt"};
};

class DoubleToken : public Token {
public:
    DoubleToken(int id, std::string label)
            : Token(id, std::move(label), true) {}
    LexerStatus tryFind(std::istream& in) override;

    FiniteStateMachine keywordCatchAllFsm{"fsm_catch_all.txt"};
    FiniteStateMachine realFsm{"fsm_real.txt"};
};

constexpr int ID_TOKEN_MAX_LENGTH =  8;
class IdToken : public Token {
public:
    IdToken(int id, std::string label)
            : Token(id, std::move(label), true) {}
    LexerStatus tryFind(std::istream& in) override;

    FiniteStateMachine keywordCatchAllFsm{"fsm_catch_all.txt"};
    FiniteStateMachine idFsm{"fsm_id.txt"};
};

#define token_map_simple(tk_id, tk_class) \
    std::make_shared<tk_class>(tk_id, #tk_id)

#define token_map_generic(tk_id, tk_class, ...) \
    std::make_shared<tk_class>(tk_id, #tk_id, __VA_ARGS__)

#define token_map_exact_text(tk_id, ...) \
    token_map_generic(tk_id, ExactTextToken, __VA_ARGS__)

#define token_map_exact_keyword(tk_id, ...) \
    token_map_generic(tk_id, ExactKeywordToken, __VA_ARGS__)

#endif //LEXERTOKENS_H
