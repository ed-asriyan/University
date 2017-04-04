cmake_minimum_required(VERSION 3.5)
project(Lab2)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES_INTERPOLATOR
        Point2d.h Point2d.cpp
        Interpolator.cpp Interpolator.h
        )
add_library(Interpolator STATIC ${SOURCE_FILES_INTERPOLATOR})

set(SOURCE_FILES_PART1
        part1.cpp
        Utils.cpp Utils.hpp
        )
add_executable(Lab2-1 ${SOURCE_FILES_PART1})
target_link_libraries(Lab2-1 Interpolator m)
