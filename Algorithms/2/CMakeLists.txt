cmake_minimum_required(VERSION 3.5)
project(Lab2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        math_functions.hpp
        Utils.cpp Utils.hpp
        Point2d.h Point2d.cpp
        Interpolator.cpp Interpolator.h
        )
add_executable(Lab2 ${SOURCE_FILES})
target_link_libraries(Lab2 m)
