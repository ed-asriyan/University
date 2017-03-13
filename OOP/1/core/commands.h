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
	SHUTDOWN,
} command_t;

typedef struct {
	const char* file_path;
} load_model_data_t;

typedef struct {
	transformation_t transformation;
} transform_object_data_t;

typedef struct {
	transformation_t transformation;
} transform_camera_data_t;

typedef union {
	load_model_data_t load_model_data;
	transform_object_data_t transform_object_data;
	transform_camera_data_t transform_camera_data;
} command_data_t;

#endif //INC_3DVIEW_COMMANDS_H
