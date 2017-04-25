cmake_minimum_required(VERSION 3.5)
project(LAB_05)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NaiveTree.h Colors.h BaseTree.h File.h)
add_executable(LAB_05 ${SOURCE_FILES})