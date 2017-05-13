cmake_minimum_required(VERSION 3.5)
project(Lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp SceneViewer/SceneViewer.cpp SceneViewer/SceneViewer.hpp)

include_directories(SceneViewer)
add_subdirectory(SceneViewer)

add_executable(Lab3 ${SOURCE_FILES})
target_link_libraries(Lab3 SceneViewer)
