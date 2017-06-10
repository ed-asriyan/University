cmake_minimum_required(VERSION 3.5)
project(3dViewCore)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        math.c math.h
        transformation.h
        canvas.h
        camera.c camera.h
        errors.h
        commands.h
        model.c model.h
        object.c object.h
        service.c service.h
        execute.c execute.h
        )
add_library(3dViewCore ${SOURCE_FILES})
target_link_libraries(3dViewCore m)
