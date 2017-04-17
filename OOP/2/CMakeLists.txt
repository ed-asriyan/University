cmake_minimum_required(VERSION 3.5)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        BaseVector.cpp BaseVector.hpp
        Iterator.hpp
        main.cpp
        )
add_executable(Lab2 ${SOURCE_FILES})