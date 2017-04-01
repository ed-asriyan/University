//
// Created by ed on 07.03.17.
//

#ifndef INC_3DVIEW_MATH_H
#define INC_3DVIEW_MATH_H

#include <math.h>

#include "transformation.h"

double to_radians(double degrees);

typedef struct {
	double x, y, z;
} vector_t;

typedef union {
	double e[4][4];
	struct {
		double
			e00, e01, e02, e03,
			e10, e11, e12, e13,
			e20, e21, e22, e23,
			e30, e31, e32, e33;
	};
} matrix_t;

extern vector_t const vector_zero;

extern vector_t const vector_unit_x;

extern vector_t const vector_unit_y;

extern vector_t const vector_unit_z;

vector_t vector_create(double x, double y, double z);
vector_t vector_neg(const vector_t* vector);
vector_t vector_add(const vector_t* vector_a, const vector_t* vector_b);
vector_t vector_sub(const vector_t* vector_a, const vector_t* vector_b);
vector_t vector_mul(const vector_t* vector, double scalar);
vector_t vector_div(const vector_t* vector, double scalar);
double vector_length(const vector_t* vector);
vector_t vector_unit(const vector_t* vector);
double vector_dot(const vector_t* vector_a, const vector_t* vector_b);
vector_t vector_cross(const vector_t* vector_a, const vector_t* vector_b);
vector_t vector_transform(const vector_t* vector, const matrix_t* matrix);

extern matrix_t const matrix_zero;

extern matrix_t const matrix_identity;

matrix_t matrix_create(const transformation_t* transformation);
matrix_t matrix_translation(const vector_t* displacement);
matrix_t matrix_rotation(const vector_t* axis, double angle);
matrix_t matrix_uniform_scaling(double factor);

matrix_t matrix_inv(const matrix_t* matrix);
matrix_t matrix_mul(const matrix_t* matrix_a, const matrix_t* matrix_b);

matrix_t matrix_transfromation_at(const matrix_t* transformation, const vector_t* position);

#endif //INC_3DVIEW_MATH_H
