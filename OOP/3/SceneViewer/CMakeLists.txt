cmake_minimum_required(VERSION 3.5)
project(SceneViewer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        SceneViewer.cpp SceneViewer.hpp
        )
add_library(Elevator ${SOURCE_FILES})