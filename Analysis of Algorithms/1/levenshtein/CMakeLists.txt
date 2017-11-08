cmake_minimum_required(VERSION 3.5)
project(levenshtein)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES
        levenshtein.c levenshtein.h
        )
add_library(levenshtein ${SOURCE_FILES})
