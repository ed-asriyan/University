cmake_minimum_required(VERSION 3.9)
project(Lab2)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(matrix)

set(SOURCE_FILES
        main.cpp
        )
add_executable(Lab2 ${SOURCE_FILES})
target_link_libraries(Lab2 matrix)
