cmake_minimum_required(VERSION 3.5)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

# interpolator library (common to all lab parts)
set(SOURCE_FILES_INTERPOLATOR
        Point1d.h Point1d.cpp
        Point2d.h Point2d.cpp
        Interpolation.hpp
        )
add_library(Interpolator STATIC ${SOURCE_FILES_INTERPOLATOR})

# functions library (common to all lab parts)
set(SOURCE_FILES_FUNCTIONS
        Point2d.h Point2d.cpp
        Functions.cpp Functions.hpp
        )
add_library(Functions STATIC ${SOURCE_FILES_FUNCTIONS})
target_link_libraries(Functions m)

# 1st lab part (interpolation)
set(SOURCE_FILES_PART1
        part1.cpp
        FuncIterator.cpp FuncIterator.hpp
        )
add_executable(Lab2-1 ${SOURCE_FILES_PART1})
target_link_libraries(Lab2-1 Functions Interpolator)

# 2nd lab part (inverse interpolation)
set(SOURCE_FILES_PART2
        part2.cpp
        Equations.cpp Equations.hpp
        )
add_executable(Lab2-2 ${SOURCE_FILES_PART2})
target_link_libraries(Lab2-2 Functions Interpolator)

# 3rd lab part (3D interpolation)
set(SOURCE_FILES_PART3
        part3.cpp
        FuncIterator.cpp FuncIterator.hpp
        )
add_executable(Lab2-3 ${SOURCE_FILES_PART3})
target_link_libraries(Lab2-3 Functions Interpolator)

# 4th lab part (spline)
set(SOURCE_FILES_PART4
        part4.cpp
        FuncIterator.cpp FuncIterator.hpp
        )
add_executable(Lab2-4 ${SOURCE_FILES_PART4})
target_link_libraries(Lab2-4 Functions Interpolator)
