//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_CAMERA_H
#define INC_3DVIEW_CAMERA_H

#include <math.h>

#include "math.h"
#include "canvas.h"

extern const double camera_default_field_of_view;

extern const double camera_default_min_distance;

extern const double camera_default_max_distance;

typedef struct {
	matrix_t to_world;
	double field_of_view;
	double min_distance, max_distance;
} camera_t;

void camera_initialize(camera_t* camera);

void camera_transform(camera_t* camera, const matrix_t* transformation);
matrix_t camera_to_canvas(const camera_t* camera, const canvas_t* canvas);

void camera_deinitialize(camera_t* camera);

#endif //INC_3DVIEW_CAMERA_H
