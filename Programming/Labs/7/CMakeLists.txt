cmake_minimum_required(VERSION 3.5)
project(StateMachine)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Wall -Werror -Wextra")

set(SOURCE_FILES main.c stack.c stack.h state_machine.c state_machine.h)
add_executable(StateMachine ${SOURCE_FILES})