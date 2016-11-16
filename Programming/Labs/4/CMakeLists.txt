cmake_minimum_required(VERSION 3.5)
project(Lists)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -Wextra")

set(SOURCE_FILES main.c LinkedList.c LinkedList.h)
add_executable(Lists ${SOURCE_FILES})