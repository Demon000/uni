#include <iostream>
#include "lexer/Lexer.h"
#include "lexer/LexerTokens.h"
#include "finite_state_machine/FiniteStateMachine.h"

#include "LexerTokenIds.h"
#include "grammar/Grammar.h"
#include "grammar/RecursiveDescentParser.h"

void runUserInput() {
    FiniteStateMachine fsm;

    while (true) {
        std::cout <<
                  "1. Read from file\n"
                  "2. Read from stdin\n"
                  "3. Print states\n"
                  "4. Print alphabet\n"
                  "5. Print transitions\n"
                  "6. Print final states\n"
                  "7. Parse\n"
                  "0. Exit\n"
                ;

        int key;

        std::cout << "Command: ";
        std::cin >> key;

        if (key == 0) {
            break;
        } else if (key == 1) {
            std::string filename;
            std::cout << "File name: ";
            std::cin >> filename;

            std::ifstream in(filename);
            fsm.read(in);
        } else if (key == 2) {
            fsm.read(std::cin);
        } else if (key == 3) {
            std::cout << fsm.statesToString();
        } else if (key == 4) {
            std::cout << "Alphabet -> " << fsm.getAlphabet() << std::endl;
        } else if (key == 5) {
            std::cout << fsm.transitionsToString();
        } else if (key == 6) {
            std::cout << fsm.finalStatesToString();
        } else if (key == 7) {
            std::cout << "Text to parse: ";

            std::string text;
            std::cin >> text;

            auto result = fsm.parse(text);
            std::cout << result.toString();
        } else {
            std::cout << "Invalid command.\n";
        }
    }
}

std::vector<std::shared_ptr<Token>> tokenDefinitions = {
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

void printProductionRules(std::vector<ProductionRule> const& rules, bool withDetails) {
    for (auto const& rule : rules) {
        std::cout << rule.toString(withDetails) << std::endl;
    }
}

void runLexer() {
    std::ifstream in("test.c.txt");
    Lexer lexer(tokenDefinitions);

    auto status = lexer.tokenize(in);
    if (status != PARSE_SUCCESS) {
        std::cout << "Failed to parse input file\n";
        std::cout << "Buffer remaining:\n";
        std::cout << in.rdbuf();
    }

    auto tokens = lexer.getTokens();
    for (auto const& token : tokens) {
        std::cout << token.toString() << std::endl;
    }

    std::ifstream cGrammarIn("c_grammar.txt");
    Grammar grammar{cGrammarIn};

    auto productionRules = grammar.getProductionRules();
    printProductionRules(productionRules, false);

    std::vector<std::string> tokenLabels;
    tokenLabels.reserve(tokens.size());
    for (auto const& token : tokens) {
        tokenLabels.push_back(token.label);
    }

    RecursiveDescentParser parser{grammar};
    std::vector<Symbol> symbols = parser.parseTokens(tokenLabels);

    for (auto const& symbol : symbols) {
        if (Symbol::isTerminal(symbol)) {
            std::cout << symbol.toString() << std::endl;
        }
    }
}

void testFSM() {
    FiniteStateMachine fsm("fsm_catch_all_keywords.txt");
    std::cout << fsm.statesToString();
    std::cout << fsm.transitionsToString();
    std::cout << fsm.finalStatesToString();

    auto result = fsm.parse("aabbbcd_321421s???");
    std::cout << result.toString();
}

int main() {
    runLexer();
//    runUserInput();
//    testFSM();

    return 0;
}
