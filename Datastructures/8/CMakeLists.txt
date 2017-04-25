cmake_minimum_required(VERSION 3.5)
project(Lab_08)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c heap.h heap.c graph.h graph.c dijkstra.c dijkstra.h)
add_executable(Lab_08 ${SOURCE_FILES})
