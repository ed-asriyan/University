cmake_minimum_required(VERSION 3.5)
project(matrix)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Matrix.hpp
        MatrixMultiplication.hpp
        )
add_library(matrix INTERFACE)
