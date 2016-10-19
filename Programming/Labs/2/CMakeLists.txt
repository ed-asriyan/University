cmake_minimum_required(VERSION 3.6)
project(EquationSystemSolver)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -lm")

set(SOURCE_FILES main.c Matrix/matrix.c Matrix/matrix.h gauss.c gauss.h iterations.c iterations.h)
add_executable(EquationSystemSolver ${SOURCE_FILES})