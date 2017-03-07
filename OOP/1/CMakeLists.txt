cmake_minimum_required(VERSION 3.5)
project(3dView)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        main.c main.c
        core/math.c core/math.h
        core/transformation.c core/transformation.h
        core/canvas.c core/canvas.h
        core/camera.c core/camera.h
        core/errors.h
        core/commands.h
        core/model.c core/model.h
        core/object.c core/object.h
        core/service.c core/service.h
        )
add_executable(3dView ${SOURCE_FILES})

target_link_libraries(3dView GL GLU glut m)