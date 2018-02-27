cmake_minimum_required(VERSION 3.4)
project(app)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(core)

add_executable(app
        main.cpp
        RouteTranslator.hpp
        )
target_link_libraries(app core)
