cmake_minimum_required(VERSION 3.6)
project(Integral)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Integral.hpp
        Equations.hpp
        )
add_executable(Integral ${SOURCE_FILES})
target_link_libraries(Integral m)