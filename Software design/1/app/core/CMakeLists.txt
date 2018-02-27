cmake_minimum_required(VERSION 3.4)
project(core)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Point.hpp
        Route.hpp
        deserializer/RouteDeserializer.hpp
        deserializer/RouteDeserializerPolyline.cpp
        deserializer/RouteDeserializerPolyline.hpp
        deserializer/RouteDeserializerGpx.cpp
        deserializer/RouteDeserializerGpx.hpp
        serializers/RouteSerializer.hpp
        serializers/RouteSerializerGpx.cpp
        serializers/RouteSerializerGpx.hpp
        serializers/RouteSerializerPolyline.cpp
        serializers/RouteSerializerPolyline.hpp
        )

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})

add_library(core ${SOURCE_FILES})
