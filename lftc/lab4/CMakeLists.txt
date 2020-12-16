cmake_minimum_required(VERSION 3.17)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab4 main.cpp Grammar.h ProductionRule.h RecursiveDescentParser.h)

configure_file(input.txt input.txt COPYONLY)
configure_file(grammar_simple.txt grammar_simple.txt COPYONLY)
configure_file(input_simple.txt input_simple.txt COPYONLY)
