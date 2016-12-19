cmake_minimum_required(VERSION 3.5)
project(Lab_07)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp
        AVLTree.h
        NaiveTree.h
        ClosedHash.h
        OpenHash.h
        BaseTree.h
        BaseHash.h
        Colors.h
        HashFunc.h
        )
add_executable(Lab_07 ${SOURCE_FILES})