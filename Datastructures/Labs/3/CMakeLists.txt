cmake_minimum_required(VERSION 3.5)
project(CustomersTable)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")

set(SOURCE_FILES main.c mio.h mio.c car.h car.c)
add_executable(CustomersTable ${SOURCE_FILES})
