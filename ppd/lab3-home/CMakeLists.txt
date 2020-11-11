cmake_minimum_required(VERSION 3.17)
project(lab3_home)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER mpic++)
set(CMAKE_CC_COMPILER mpicc)

add_executable(lab3_home main.cpp manual.cpp scatter_gather.cpp iterative.cpp)

configure_file(Numar1.txt Numar1.txt COPYONLY)
configure_file(Numar2.txt Numar2.txt COPYONLY)

find_package(MPI)
include_directories(${MPI_INCLUDE_PATH})
target_link_libraries(lab3_home ${MPI_LIBRARIES})
