cmake_minimum_required(VERSION 3.5)
project(Lab4)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)

include_directories(Elevator)
add_subdirectory(Elevator)

add_executable(Lab4 ${SOURCE_FILES})
target_link_libraries(Lab4 Elevator)
