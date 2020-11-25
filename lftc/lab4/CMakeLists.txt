cmake_minimum_required(VERSION 3.17)
project(lab4)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab4 main.cpp Grammar.h ProductionRule.h)

configure_file(input.txt input.txt COPYONLY)
