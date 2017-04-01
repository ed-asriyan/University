//
// Created by ed on 07.03.17.
//

#include "object.h"

void object_initialize(object_t* object) {
	object->to_world = matrix_identity;
	model_initialize(&object->model);
}

error_t object_load_model(object_t* object, const char* file_path) {
	error_t error = model_load(&object->model, file_path);
	if (error == NONE) {
		object->to_world = matrix_identity;
	}
	return error;
}

bool object_model_is_loaded(const object_t* object) {
	return model_is_loaded(&object->model);
}

error_t object_transform(object_t* object, const matrix_t* transformation) {
	error_t error = NONE;
	if (object_model_is_loaded(object)) {
		object->to_world = matrix_mul(&object->to_world, transformation);
	} else {
		error = MODEL_NOT_LOADED;
	}
	return error;
}

error_t object_render(const object_t* object, const camera_t* camera, const canvas_t* canvas) {
	const matrix_t matrix_b = matrix_inv(&camera->to_world);
	matrix_t object_to_camera = matrix_mul(&object->to_world, &matrix_b);
	const matrix_t b = camera_to_canvas(camera, canvas);
	matrix_t object_to_canvas = matrix_mul(&object_to_camera, &b);
	return model_render(&object->model, &object_to_canvas, canvas);
}

void object_deinitialize(object_t* object) {
	model_deinitialize(&object->model);
}
