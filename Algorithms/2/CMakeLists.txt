cmake_minimum_required(VERSION 3.5)
project(Lab2)

set(CMAKE_CXX_STANDARD 14)

# interpolator library (common to all lab parts)
set(SOURCE_FILES_INTERPOLATOR
        Point2d.h Point2d.cpp
        Interpolation.hpp
        )
add_library(Interpolator STATIC ${SOURCE_FILES_INTERPOLATOR})

# 1st lab part (interpolation)
set(SOURCE_FILES_PART1
        part1.cpp
        FuncIterator.cpp FuncIterator.hpp
        )
add_executable(Lab2-1 ${SOURCE_FILES_PART1})
target_link_libraries(Lab2-1 Interpolator m)

# 2nd lab part (inverse interpolation)
set(SOURCE_FILES_PART2
        part2.cpp
        Equations.cpp Equations.hpp
        )
add_executable(Lab2-2 ${SOURCE_FILES_PART2})
target_link_libraries(Lab2-2 Interpolator m)
