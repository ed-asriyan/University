cmake_minimum_required(VERSION 3.5)
project(Lab4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        derivative.hpp
        )
add_executable(Lab4 ${SOURCE_FILES})
