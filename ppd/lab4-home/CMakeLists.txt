cmake_minimum_required(VERSION 3.17)
project(lab4_home)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab4_home main.cpp Queue.h Polynomial.h PolynomialStreamsGenerator.h PolynomialStream.h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(lab4_home PRIVATE Threads::Threads)
