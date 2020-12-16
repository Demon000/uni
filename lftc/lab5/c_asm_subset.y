%{
int yylex();
void yyerror(const char *s);
%}

%define parse.error verbose

%token TK_OP_EQUAL
%token TK_OP_NOT_EQUAL
%token TK_OP_LESS_EQUAL
%token TK_OP_GREATER_EQUAL
%token TK_OP_LESS
%token TK_OP_GREATER
%token TK_OP_BW_AND
%token TK_OP_ASSIGN
%token TK_OP_PLUS
%token TK_OP_MINUS
%token TK_OP_MULTIPLY
%token TK_OP_DIVIDE
%token TK_OP_MOD
%token TK_LEFT_BRACE
%token TK_LEFT_PAREN
%token TK_RIGHT_BRACE
%token TK_RIGHT_PAREN
%token TK_SEMICOLON
%token TK_COMMA
%token TK_KEYWORD_DOUBLE
%token TK_KEYWORD_INT
%token TK_KEYWORD_IF
%token TK_KEYWORD_ELSE
%token TK_KEYWORD_FOR
%token TK_KEYWORD_WHILE
%token TK_KEYWORD_RETURN
%token TK_KEYWORD_BREAK
%token TK_CONST_STR
%token TK_CONST_FLOAT
%token TK_CONST_INT
%token TK_ID

%start program

%%

program
	: function_list
	;

function_list
	: function function_list
	| function
	;

function
	: function_prototype scope
	;

function_prototype
	: data_type TK_ID TK_LEFT_PAREN TK_RIGHT_PAREN
	| data_type TK_ID TK_LEFT_PAREN argument_list TK_RIGHT_PAREN
	;

argument_list
	: argument argument_list
	| argument
	;

argument
	: data_type TK_ID
	;


instruction_list
	: instruction instruction_list
	| instruction
	;

instruction
	: variable_declaration TK_SEMICOLON
	| variable_assignment TK_SEMICOLON
	| function_call TK_SEMICOLON
	| return TK_SEMICOLON
	;

variable_declaration
	: data_type variable_assignment_list
	;

variable_assignment_list
	: variable_assignment_opt TK_COMMA variable_assignment_list
	| variable_assignment_opt
	;

variable_assignment_opt
	: variable_assignment
	| TK_ID
	;

variable_assignment
	: TK_ID TK_OP_ASSIGN expression
	;

function_call
	: TK_ID TK_LEFT_PAREN function_argument_list TK_RIGHT_PAREN
	;

function_argument_list
	: expression TK_COMMA function_argument_list
	| expression
	;

return
	: TK_KEYWORD_RETURN expression
	;

expression
	: expression_l operator expression
	| expression_l
	;

expression_l
        : TK_CONST_STR
        | TK_CONST_INT
        | TK_OP_BW_AND TK_ID
        | TK_ID
        ;

operator
	: TK_OP_MULTIPLY
	| TK_OP_DIVIDE
	| TK_OP_MOD
	| TK_OP_MINUS
	| TK_OP_PLUS
	;

data_type
	: TK_KEYWORD_INT
	;

scope
	: scope_start instruction_list scope_end
	;

scope_start
	: TK_LEFT_BRACE
	;

scope_end
	: TK_RIGHT_BRACE
	;

%%

#include <stdio.h>

extern int yylineno;

void yyerror(const char *s)
{
	fflush(stdout);
	fprintf(stderr, "*** %d %s\n", yylineno, s);
}

int main(int argc, char **argv)
{
#ifdef YYDEBUG
	yydebug = 1;
#endif

	yyparse();
	return 0;
}
