cmake_minimum_required(VERSION 3.17)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab3 main.cpp)

find_package(MPI)
include_directories(${MPI_INCLUDE_PATH})
target_link_libraries(lab3 ${MPI_LIBRARIES})
