//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_COMMANDS_H
#define INC_3DVIEW_COMMANDS_H

#include "transformation.h"
#include "canvas.h"

typedef enum {
	STARTUP,
	LOAD_MODEL,
	TRANSFORM_OBJECT,
	TRANSFORM_CAMERA,
	RENDER,
	UNLOAD_MODEL,
	SHUTDOWN,
} command_t;

typedef struct {
} startup_data_t;

typedef struct {
	char const* file_path;
} load_model_data_t;

typedef struct {
	transformation_t transformation;
} transform_object_data_t;

typedef struct {
	transformation_t transformation;
} transform_camera_data_t;

typedef struct {
	canvas_t* canvas;
} render_data_t;

typedef struct {
} unload_model_data_t;

typedef struct {
} shutdown_data_t;

typedef union {
	startup_data_t startup_data;
	load_model_data_t load_model_data;
	transform_object_data_t transform_object_data;
	transform_camera_data_t transform_camera_data;
	render_data_t render_data;
	unload_model_data_t unload_model_data;
	shutdown_data_t shutdown_data;
} command_data_t;

#endif //INC_3DVIEW_COMMANDS_H
