cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp Lexer.cpp Lexer.h BinarySearchTree.h FiniteStateMachine.h FiniteStateMachine.cpp StreamUtils.cpp StreamUtils.h)
configure_file(test.c.txt test.c.txt COPYONLY)
configure_file(fsm_catch_all_keyword.txt fsm_catch_all_keyword.txt COPYONLY)
configure_file(fsm_integer.txt fsm_integer.txt COPYONLY)
configure_file(fsm_real.txt fsm_real.txt COPYONLY)
