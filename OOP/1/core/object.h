//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_OBJECT_H
#define INC_3DVIEW_OBJECT_H

#include "math.h"
#include "model.h"
#include "errors.h"
#include "camera.h"
#include "canvas.h"

typedef struct {
	matrix_t to_world;
	model_t model;
} object_t;

void object_initialize(object_t* object);
error_t object_load_model(object_t* object, const char* file_path);
bool object_model_is_loaded(const object_t* object);
error_t object_transform(object_t* object, const matrix_t* transformation);
error_t object_render(const object_t* object, const camera_t* camera);
void object_deinitialize(object_t* object);

#endif //INC_3DVIEW_OBJECT_H
