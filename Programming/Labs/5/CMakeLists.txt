cmake_minimum_required(VERSION 3.6)
project(DoubleChecker)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -Wextra")

set(SOURCE_FILES main.c)
add_executable(DoubleChecker ${SOURCE_FILES})