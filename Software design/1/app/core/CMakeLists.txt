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

add_library(core ${SOURCE_FILES})
