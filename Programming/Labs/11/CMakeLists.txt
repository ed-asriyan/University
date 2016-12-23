cmake_minimum_required(VERSION 3.5)
project(BinaryTree)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c BinaryTree.h BinaryTree.c Object.h ParseXML.h ParseXML.c)
add_executable(BinaryTree ${SOURCE_FILES})