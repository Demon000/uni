#ifndef LEXER_H
#define LEXER_H

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
	Token(enum TokenId id, std::string label, std::string buffer)
			: id(id), label(std::move(label)), buffer(std::move(buffer)) {}
    Token() : Token(TK_DEFAULT, "", "") {}

	bool isIndexed() const {
		switch (id) {
		case TK_CONST_DOUBLE:
		case TK_CONST_INT:
		case TK_CONST_STRING:
		case TK_ID:
			return true;
		default:
			return false;
		}
	}

	enum TokenId id;
	int index = 0;
	std::string buffer;
	std::string label;
};

class IndexedTokenValue {
public:
	IndexedTokenValue(std::string buffer)
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

#endif // LEXER_H
