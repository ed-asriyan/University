cmake_minimum_required(VERSION 3.5)
project(Queue)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp LoopedArray.h Queue.h QueueArray.h QueueList.h RequestUnit.h ServiceUnit.h RandomGenerator.cpp RandomGenerator.h QueueTests.h)
add_executable(Queue ${SOURCE_FILES})