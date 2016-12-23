cmake_minimum_required(VERSION 3.5)
project(Graph)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c heap.h heap.c graph.h graph.c dijkstra.c dijkstra.h)
add_executable(Graph ${SOURCE_FILES})