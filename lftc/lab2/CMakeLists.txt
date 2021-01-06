cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp Lexer.cpp Lexer.h BinarySearchTree.h FiniteStateMachine.h FiniteStateMachine.cpp StreamUtils.cpp StreamUtils.h LexerTokens.h LexerTokenIds.h LexerStatus.h)
configure_file(test.c.txt test.c.txt COPYONLY)
configure_file(fsm_catch_all.txt fsm_catch_all.txt COPYONLY)
configure_file(fsm_integer.txt fsm_integer.txt COPYONLY)
configure_file(fsm_real.txt fsm_real.txt COPYONLY)
configure_file(fsm_id.txt fsm_id.txt COPYONLY)
