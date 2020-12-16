%{
#include "c_subset.tab.h"
%}

%option yylineno

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

%%

"=="					{ return TK_OP_EQUAL; }
"!="					{ return TK_OP_NOT_EQUAL; }
"<="					{ return TK_OP_LESS_EQUAL; }
">="					{ return TK_OP_GREATER_EQUAL; }
"<"						{ return TK_OP_LESS; }
">"						{ return TK_OP_GREATER; }
"&"						{ return TK_OP_BW_AND; }

"="						{ return TK_OP_ASSIGN; }
"+"						{ return TK_OP_PLUS; }
"-"						{ return TK_OP_MINUS; }
"*"						{ return TK_OP_MULTIPLY; }
"/"						{ return TK_OP_DIVIDE; }
"%"						{ return TK_OP_MOD; }

"{"						{ return TK_LEFT_BRACE; }
"("						{ return TK_LEFT_PAREN; }
"}"						{ return TK_RIGHT_BRACE; }
")"						{ return TK_RIGHT_PAREN; }
";"						{ return TK_SEMICOLON; }
","						{ return TK_COMMA; }

"double"				{ return TK_KEYWORD_DOUBLE; }
"int"					{ return TK_KEYWORD_INT; }

"if"					{ return TK_KEYWORD_IF; }
"else"					{ return TK_KEYWORD_ELSE; }
"for"					{ return TK_KEYWORD_FOR; }
"while"					{ return TK_KEYWORD_WHILE; }

"return"				{ return TK_KEYWORD_RETURN; }
"break"					{ return TK_KEYWORD_BREAK; }

\"(\\.|[^"\\])*\"					{ return TK_CONST_STR; }

{SIGN}{DEC_START}{DEC}*.{DEC}+		{ return TK_CONST_FLOAT; }
{SIGN}0.{DEC}+						{ return TK_CONST_FLOAT; }

{SIGN}0						{ return TK_CONST_INT; }
{SIGN}{HEX_START}{HEX}*		{ return TK_CONST_INT; }
{SIGN}{OCT_START}{OCT}*		{ return TK_CONST_INT; }
{SIGN}{BIN_START}{BIN}*		{ return TK_CONST_INT; }
{SIGN}{DEC_START}{DEC}*		{ return TK_CONST_INT; }

{ID_START}{ID}*				{ return TK_ID; }

{WS}+					{}
.						{}

%%
