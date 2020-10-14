cmake_minimum_required(VERSION 3.17)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab2 main.cpp Lexer.cpp Lexer.h utils.cpp utils.h)
configure_file(test.c.txt test.c.txt COPYONLY)
