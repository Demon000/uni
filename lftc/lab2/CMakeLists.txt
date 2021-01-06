cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2
        main.cpp
        LexerTokenIds.h
        lexer/Lexer.cpp
        lexer/Lexer.h
        binary_search_tree/BinarySearchTree.h
        finite_state_machine/FiniteStateMachine.h
        finite_state_machine/FiniteStateMachine.cpp
        stream_utils/StreamUtils.cpp
        stream_utils/StreamUtils.h
        lexer/LexerTokens.h
        lexer/LexerStatus.h
        grammar/Grammar.h
        grammar/ProductionRule.h
        grammar/RecursiveDescentParser.h
)
configure_file(test.c.txt test.c.txt COPYONLY)
configure_file(c_grammar.txt c_grammar.txt COPYONLY)
configure_file(lexer/fsm_catch_all.txt lexer/fsm_catch_all.txt COPYONLY)
configure_file(lexer/fsm_integer.txt lexer/fsm_integer.txt COPYONLY)
configure_file(lexer/fsm_real.txt lexer/fsm_real.txt COPYONLY)
configure_file(lexer/fsm_id.txt lexer/fsm_id.txt COPYONLY)
