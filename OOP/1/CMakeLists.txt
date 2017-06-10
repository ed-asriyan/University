cmake_minimum_required(VERSION 3.5)
project(3dView)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        main.c
        point.h
        )

add_subdirectory(core)

add_executable(3dView ${SOURCE_FILES})
target_link_libraries(3dView 3dViewCore GL GLU glut)
