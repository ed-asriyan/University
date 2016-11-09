cmake_minimum_required(VERSION 3.6)
project(LCS)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -Wextra")

set(SOURCE_FILES main.c lcs.c lcs.h)
add_executable(LCS ${SOURCE_FILES})