cmake_minimum_required(VERSION 3.17)
project(lab0_cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab0_cpp main.cpp PPDUtils.cpp PPDUtils.h)
configure_file(first.txt first.txt COPYONLY)
configure_file(second.txt second.txt COPYONLY)