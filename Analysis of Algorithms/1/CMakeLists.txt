cmake_minimum_required(VERSION 3.5)
project(Lab1)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        main.c
        levenshtein.c levenshtein.h
        )
add_executable(Lab1 ${SOURCE_FILES})
