cmake_minimum_required(VERSION 3.5)
project(EquationSystemSolver)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -Wextra")

set(SOURCE_FILES main.c Matrix/matrix.c Matrix/matrix.h gauss.c gauss.h iterations.c iterations.h)

add_executable(EquationSystemSolver ${SOURCE_FILES})
target_link_libraries(EquationSystemSolver m)
