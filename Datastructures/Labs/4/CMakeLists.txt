cmake_minimum_required(VERSION 3.6)
project(Queue)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Queue ${SOURCE_FILES})