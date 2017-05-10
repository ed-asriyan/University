cmake_minimum_required(VERSION 3.5)
project(Elevator)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost COMPONENTS signals)

set(SOURCE_FILES
        Elevator.cpp Elevator.hpp
        )
add_library(Elevator ${SOURCE_FILES})
