//
// Created by ed on 07.03.17.
//

#include "camera.h"

double const camera_default_field_of_view = M_PI / 3; //to_radians(60.0);
double const camera_default_min_distance = 0.01;

double const camera_default_max_distance = 100.0;

void camera_initialize(camera_t* camera) {
	camera->to_world = matrix_identity;
	camera->field_of_view = camera_default_field_of_view;
	camera->min_distance = camera_default_min_distance;
	camera->max_distance = camera_default_max_distance;
}

void camera_transform(camera_t* camera, const matrix_t* transformation) {
	const matrix_t a = camera->to_world;
	camera->to_world = matrix_mul(&a, transformation);
}

static matrix_t camera_to_ndc(const camera_t* camera, double aspect_ratio) {
	double factor = 1.0 / tan(camera->field_of_view / 2.0);
	matrix_t result = matrix_zero;
	result.e00 = factor / aspect_ratio;
	result.e11 = factor;
	result.e22 = (camera->min_distance + camera->max_distance) / (camera->min_distance - camera->max_distance);
	result.e23 = -1.0;
	result.e32 = 2.0 * camera->min_distance * camera->max_distance / (camera->min_distance - camera->max_distance);
	return result;
}

static matrix_t ndc_to_canvas(double width, double height) {
	matrix_t result = matrix_identity;
	result.e00 = width / 2.0;
	result.e11 = -height / 2.0;
	result.e22 = 0.0;
	result.e30 = width / 2.0;
	result.e31 = height / 2.0;
	return result;
}

matrix_t camera_to_canvas(const camera_t* camera) {
	double width = get_width(), height = get_height();
	double aspect_ratio = width / height;
	const matrix_t a = camera_to_ndc(camera, aspect_ratio);
	const matrix_t b = ndc_to_canvas(width, height);
	return matrix_mul(&a, &b);
}

void camera_deinitialize(camera_t* camera) {
	// nothing
}