cmake_minimum_required(VERSION 3.5)
project(ExpressionSolver)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -Wextra")

set(SOURCE_FILES main.c StackChar.c StackChar.h StackInt.c StackInt.h)
add_executable(ExpressionSolver ${SOURCE_FILES})
target_link_libraries(ExpressionSolver m)