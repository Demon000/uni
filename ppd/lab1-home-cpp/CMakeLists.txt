cmake_minimum_required(VERSION 3.17)
project(lab1_home_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-lpthread")

add_executable(lab1_home_cpp main.cpp Image.h StaticImage.h DynamicImage.h ImageProcessingUtils.h ImageProcessingThread.h AverageImageProcessingThread.h)
