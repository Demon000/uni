SIGN		([+-])?

HEX_START	(0[xX])
HEX			[a-fA-F0-9]

DEC_START	[1-9]
DEC 		[0-9]

OCT_START	(0)
OCT			[0-7]

BIN_START	(0b)
BIN			[0-1]

ID_START	[a-zA-Z_]
ID			[a-zA-Z0-9_]

WS  [ \t\v\n\f]

%{
#include <cstdlib>
#include <iostream>
#include <vector>

#include "Lexer.h"
#include "BinarySearchTree.h"

extern "C" {
	int yylex();
};

std::vector<Token> tokens;
BinarySearchTree<IndexedTokenValue> identifiers;
BinarySearchTree<IndexedTokenValue> constants;

void insertSimpleToken(Token & token) {
	tokens.push_back(token);
}

void insertIndexedToken(Token & token) {
    IndexedTokenValue value(token.buffer);

    Node<IndexedTokenValue> *node;
    if (token.id == TK_ID) {
        node = identifiers.insertNode(value, true);
    } else {
        node = constants.insertNode(value, true);
    }
    token.index = node->data.index = node->index;

    insertSimpleToken(token);
}

enum TokenId insertToken(enum TokenId id, std::string const& label, std::string const& buffer) {
	Token token(id, label, buffer);
	if (token.isIndexed()) {
		insertIndexedToken(token);
	} else {
		insertSimpleToken(token);
	}

	return id;
}

#define token_map(tk_id) \
	return insertToken(tk_id, std::string(#tk_id), std::string(yytext));

%}

%%
"=="					{ token_map(TK_OP_EQUAL); }
"!="					{ token_map(TK_OP_NOT_EQUAL); }
"<="					{ token_map(TK_OP_LESS_EQUAL); }
">="					{ token_map(TK_OP_GREATER_EQUAL); }
"<"						{ token_map(TK_OP_LESS); }
">"						{ token_map(TK_OP_GREATER); }
"&"						{ token_map(TK_OP_BW_AND); }

"="						{ token_map(TK_OP_ASSIGN); }
"+"						{ token_map(TK_OP_PLUS); }
"-"						{ token_map(TK_OP_MINUS); }
"*"						{ token_map(TK_OP_MULTIPLY); }
"/"						{ token_map(TK_OP_DIVIDE); }
"%"						{ token_map(TK_OP_MOD); }

"{"						{ token_map(TK_LEFT_BRACE); }
"("						{ token_map(TK_LEFT_PAREN); }
"}"						{ token_map(TK_RIGHT_BRACE); }
")"						{ token_map(TK_RIGHT_PAREN); }
";"						{ token_map(TK_SEMICOLON); }
","						{ token_map(TK_COMMA); }

"double"				{ token_map(TK_KEYWORD_DOUBLE); }
"int"					{ token_map(TK_KEYWORD_INT); }

"if"					{ token_map(TK_KEYWORD_IF); }
"else"					{ token_map(TK_KEYWORD_ELSE); }
"for"					{ token_map(TK_KEYWORD_FOR); }
"while"					{ token_map(TK_KEYWORD_WHILE); }

"return"				{ token_map(TK_KEYWORD_RETURN); }
"break"					{ token_map(TK_KEYWORD_BREAK); }

\"(\\.|[^"\\])*\"					{ token_map(TK_CONST_STRING); }

{SIGN}{DEC_START}{DEC}*.{DEC}+		{ token_map(TK_CONST_DOUBLE); }
{SIGN}0.{DEC}+						{ token_map(TK_CONST_DOUBLE); }

{SIGN}0						{ token_map(TK_CONST_INT); }
{SIGN}{HEX_START}{HEX}*		{ token_map(TK_CONST_INT); }
{SIGN}{OCT_START}{OCT}*		{ token_map(TK_CONST_INT); }
{SIGN}{BIN_START}{BIN}*		{ token_map(TK_CONST_INT); }
{SIGN}{DEC_START}{DEC}*		{ token_map(TK_CONST_INT); }

{ID_START}{ID}*				{ token_map(TK_ID); }

{WS}+					{}
.						{}

%%

void describeTokens(const std::vector<Token>& tokens,
                           std::ostream& out) {
    out << "Id\tBuffer\tLabel\tValue index" << std::endl;
    for (const auto& token : tokens) {
        if (token.isIndexed()) {
            out << token.id << "\t" << token.buffer << "\t" << token.label << "\t" << token.index << std::endl;
        } else {
            out << token.id << "\t" << token.buffer << "\t" << token.label  << "\t" << "-" << std::endl;
        }
    }
}

void describeIndexedTokenValues(const std::vector<IndexedTokenValue>& values,
                                       std::ostream& out) {
    out << "Id\tValue" << std::endl;
    for (const auto& value : values) {
        out << value.index << "\t" << value.buffer << std::endl;
    }
}

void describe(std::ostream& out) {
    out << "Tokens" << std::endl;
    describeTokens(tokens, out);
    out << std::endl;

    out << "Identifiers" << std::endl;
    describeIndexedTokenValues(identifiers.linear(), out);
    out << std::endl;

    out << "Constants" << std::endl;
    describeIndexedTokenValues(constants.linear(), out);
    out << std::endl;
}

int main(int argc, char **argv)
{
	while (yylex());
	describe(std::cout);
}
