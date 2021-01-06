#ifndef LEXERTOKENIDS_H
#define LEXERTOKENIDS_H

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

#endif //LEXERTOKENIDS_H
