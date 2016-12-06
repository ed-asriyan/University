cmake_minimum_required(VERSION 3.5)
project(Graphs)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c graph.c graph.h dequeue.h dequeue.c)
add_executable(Graphs ${SOURCE_FILES})