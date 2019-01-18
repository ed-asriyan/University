cmake_minimum_required(VERSION 3.5)
project(Lab1)

set(CMAKE_C_STANDARD 99)

add_subdirectory(levenshtein)

set(SOURCE_FILES_LAB1
        main.c
        )
add_executable(Lab1 ${SOURCE_FILES_LAB1})
target_link_libraries(Lab1 levenshtein)

set(SOURCE_FILES_TEST
        test.c
        )
add_executable(Test ${SOURCE_FILES_TEST})
target_link_libraries(Test levenshtein)
