cmake_minimum_required(VERSION 3.4)
project(app)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(core)

add_executable(app
        main.cpp
        RouteTranslator.hpp
        )
target_link_libraries(app core)

# installing the dependency
set(destinationfile ${CMAKE_SOURCE_DIR}/crow_all.h)
if (NOT EXISTS ${destinationfile})
    execute_process(COMMAND wget https://github.com/ipkn/crow/releases/download/v0.1/crow_all.h -O ${destinationfile})
endif ()
find_package(Boost COMPONENTS thread)
target_link_libraries(app ${Boost_LIBRARIES})
target_link_libraries(app boost_thread-mt pthread)
