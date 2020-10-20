#ifndef LAB2_LEXER_H
#define LAB2_LEXER_H

#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <map>
#include <memory>
#include "BinarySearchTree.h"

enum LexerStatus {
    REACHED_EOF,
    READ_INVALID,
    READ_SUCCESS,
    FIND_TOKEN_SUCCESS,
    FIND_TOKEN_FAILED,
    SKIP_WHITESPACE_SUCCESS,
    PARSE_SUCCESS,
};

enum TokenId {
    TK_DEFAULT,

    /*
     * Operators
     */
    TK_OP_EQUAL,
    TK_OP_NOT_EQUAL,
    TK_OP_LESS_EQUAL,
    TK_OP_GREATER_EQUAL,
    TK_OP_LESS,
    TK_OP_GREATER,
    TK_OP_ASSIGN,
    TK_OP_PLUS,
    TK_OP_MINUS,
    TK_OP_MULTIPLY,
    TK_OP_DIVIDE,
    TK_OP_MOD,
    TK_OP_BW_AND,

    /*
     * Other
     */
    TK_LEFT_BRACE,
    TK_LEFT_PAREN,
    TK_RIGHT_BRACE,
    TK_RIGHT_PAREN,
    TK_SEMICOLON,
    TK_COMMA,

    /*
     * Type keywords
     */
    TK_KEYWORD_DOUBLE,
    TK_KEYWORD_INT,

    /*
     * Flow control keywords
     */
    TK_KEYWORD_IF,
    TK_KEYWORD_ELSE,
    TK_KEYWORD_FOR,
    TK_KEYWORD_WHILE,
    TK_KEYWORD_RETURN,
    TK_KEYWORD_BREAK,

    /*
     * Constants
     */
    TK_CONST_DOUBLE,
    TK_CONST_INT,
    TK_CONST_STRING,
    TK_ID,
};

class Token {
public:
    Token(enum TokenId id, std::string label, bool isIndexed=false)
            : id(id), label(std::move(label)), isIndexed_(isIndexed) {}
    Token() : Token(TK_DEFAULT, "") {}

    enum LexerStatus readOfSize(std::istream& in, size_t size);
    enum LexerStatus readValidWord(std::istream& in, const std::string& validChars);
    enum LexerStatus readValidChar(std::istream& in, const std::string& validChars);
    void putLastBack(std::istream& in);
    void putBufferBack(std::istream& in);
    virtual enum LexerStatus tryFind(std::istream& in);
    bool isIndexed() { return isIndexed_; };

    bool isIndexed_;
    enum TokenId id;
    int index = 0;
    std::string buffer;
    std::string label;
};

class TextToken : public Token {
public:
    TextToken(enum TokenId id, std::string label, std::string textMatch)
            : Token(id, std::move(label)), textMatch(std::move(textMatch)) {
    }
protected:
    std::string textMatch;
};

class ExactTextToken : public TextToken {
public:
    using TextToken::TextToken;
    enum LexerStatus tryFind(std::istream& in) override;
};

#define VALID_CATCH_ALL_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"

class ExactKeywordToken : public TextToken {
public:
    using TextToken::TextToken;
    enum LexerStatus tryFind(std::istream& in) override;
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
    DelimitedTextToken(enum TokenId id, std::string label, std::string start, std::string end)
            : Token(id, std::move(label), true), start(std::move(start)), end(std::move(end)) {
    }

    enum LexerStatus tryFind(std::istream& in) override;

private:
    std::string start;
    std::string end;
};

class IntToken : public Token {
public:
    IntToken(enum TokenId id, std::string label)
            : Token(id, std::move(label), true) {}
    enum LexerStatus tryFind(std::istream& in) override;
};

class DoubleToken : public Token {
public:
    DoubleToken(enum TokenId id, std::string label)
            : Token(id, std::move(label), true) {}
    enum LexerStatus tryFind(std::istream& in) override;
};

constexpr int ID_TOKEN_MAX_LENGTH =  8;
class IdToken : public Token {
public:
    IdToken(enum TokenId id, std::string label)
            : Token(id, std::move(label), true) {}
    enum LexerStatus tryFind(std::istream& in) override;
};

#define token_map_simple(tk_id, tk_class) \
    std::make_shared<tk_class>(tk_id, #tk_id)

#define token_map_generic(tk_id, tk_class, ...) \
    std::make_shared<tk_class>(tk_id, #tk_id, __VA_ARGS__)

#define token_map_exact_text(tk_id, ...) \
    token_map_generic(tk_id, ExactTextToken, __VA_ARGS__)

#define token_map_exact_keyword(tk_id, ...) \
    token_map_generic(tk_id, ExactKeywordToken, __VA_ARGS__)

static std::vector<std::shared_ptr<Token>> tokenDefinitions {
        token_map_exact_text(TK_OP_EQUAL, "=="),
        token_map_exact_text(TK_OP_NOT_EQUAL, "!="),
        token_map_exact_text(TK_OP_LESS_EQUAL, "<="),
        token_map_exact_text(TK_OP_GREATER_EQUAL, ">="),
        token_map_exact_text(TK_OP_LESS, "<"),
        token_map_exact_text(TK_OP_GREATER, ">"),
        token_map_exact_text(TK_OP_BW_AND, "&"),

        token_map_exact_text(TK_OP_ASSIGN, "="),
        token_map_exact_text(TK_OP_PLUS, "+"),
        token_map_exact_text(TK_OP_MINUS, "-"),
        token_map_exact_text(TK_OP_MULTIPLY, "*"),
        token_map_exact_text(TK_OP_DIVIDE, "/"),
        token_map_exact_text(TK_OP_MOD, "%"),

        token_map_exact_text(TK_LEFT_BRACE, "{"),
        token_map_exact_text(TK_LEFT_PAREN, "("),
        token_map_exact_text(TK_RIGHT_BRACE, "}"),
        token_map_exact_text(TK_RIGHT_PAREN, ")"),
        token_map_exact_text(TK_SEMICOLON, ";"),
        token_map_exact_text(TK_COMMA, ","),

        token_map_exact_keyword(TK_KEYWORD_DOUBLE, "double"),
        token_map_exact_keyword(TK_KEYWORD_INT, "int"),

        token_map_exact_keyword(TK_KEYWORD_IF, "if"),
        token_map_exact_keyword(TK_KEYWORD_ELSE, "else"),
        token_map_exact_keyword(TK_KEYWORD_FOR, "for"),
        token_map_exact_keyword(TK_KEYWORD_WHILE, "while"),

        token_map_exact_keyword(TK_KEYWORD_RETURN, "return"),
        token_map_exact_keyword(TK_KEYWORD_BREAK, "break"),

        token_map_generic(TK_CONST_STRING, DelimitedTextToken, "\"", "\""),

        token_map_simple(TK_CONST_DOUBLE, DoubleToken),
        token_map_simple(TK_CONST_INT, IntToken),

        token_map_simple(TK_ID, IdToken),
};

class Lexer {
public:
    static enum LexerStatus skipWhitespace(std::istream& in);
    LexerStatus tokenize(std::istream& in);
    void describe(std::ostream& out);

    enum LexerStatus status;
private:
    void insertToken(std::shared_ptr<Token> token);
    void insertIndexedToken(std::shared_ptr<Token> token);
    void insertSimpleToken(std::shared_ptr<Token> token);
    void describeTokens(const std::vector<std::shared_ptr<Token>> &tokens, std::ostream &out);
    void describeIndexedTokenValues(const std::vector<IndexedTokenValue> &values, std::ostream &out);

    std::vector<std::shared_ptr<Token>> tokens_;
    BinarySearchTree<IndexedTokenValue> identifiers_;
    BinarySearchTree<IndexedTokenValue> constants_;

};


#endif //LAB2_LEXER_H
