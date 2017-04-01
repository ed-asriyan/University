//
// Created by ed on 07.03.17.
//

#include "math.h"

double to_radians(double degrees) {
	return degrees * (3.1415926535897932384 / 180.0);
}

const vector_t vector_zero = {
	0.0, 0.0, 0.0
};

const vector_t vector_unit_x = {
	1.0, 0.0, 0.0
};

const vector_t vector_unit_y = {
	0.0, 1.0, 0.0
};

const vector_t vector_unit_z = {
	0.0, 0.0, 1.0
};

vector_t vector_create(double x, double y, double z) {
	vector_t r = {x, y, z};
	return r;
}

vector_t vector_neg(const vector_t* v) {
	return vector_create(-v->x, -v->y, -v->z);
}

vector_t vector_add(const vector_t* a, const vector_t* b) {
	return vector_create(a->x + b->x, a->y + b->y, a->z + b->z);
}

vector_t vector_sub(const vector_t* a, const vector_t* b) {
	return vector_create(a->x - b->x, a->y - b->y, a->z - b->z);
}

vector_t vector_mul(const vector_t* v, double s) {
	return vector_create(v->x * s, v->y * s, v->z * s);
}

vector_t vector_div(const vector_t* v, double s) {
	return vector_create(v->x / s, v->y / s, v->z / s);
}

double vector_length(const vector_t* v) {
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

vector_t vector_unit(const vector_t* v) {
	return vector_div(v, vector_length(v));
}

double dot(const vector_t* a, const vector_t* b) {
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

vector_t vector_cross(const vector_t* a, const vector_t* b) {
	return vector_create(
		a->y * b->z - a->z * b->y,
		a->z * b->x - a->x * b->z,
		a->x * b->y - a->y * b->x
	);
}

vector_t vector_transform(const vector_t* v, const matrix_t* m) {
	double x = v->x * m->e00 + v->y * m->e10 + v->z * m->e20 + m->e30;
	double y = v->x * m->e01 + v->y * m->e11 + v->z * m->e21 + m->e31;
	double z = v->x * m->e02 + v->y * m->e12 + v->z * m->e22 + m->e32;
	double w = v->x * m->e03 + v->y * m->e13 + v->z * m->e23 + m->e33;
	return vector_create(x / w, y / w, z / w);
}

const matrix_t matrix_zero = {{
	                              {0.0, 0.0, 0.0, 0.0},
	                              {0.0, 0.0, 0.0, 0.0},
	                              {0.0, 0.0, 0.0, 0.0},
	                              {0.0, 0.0, 0.0, 0.0},
                              }};

const matrix_t matrix_identity = {{
	                                  {1.0, 0.0, 0.0, 0.0},
	                                  {0.0, 1.0, 0.0, 0.0},
	                                  {0.0, 0.0, 1.0, 0.0},
	                                  {0.0, 0.0, 0.0, 1.0},
                                  }};

matrix_t matrix_from_translation(const translation_t* t) {
	const vector_t displacement = vector_create(t->displacement_x, t->displacement_y, t->displacement_z);
	return matrix_translation(&displacement);
}

matrix_t matrix_from_rotation(const rotation_t* r) {
	const vector_t v = vector_create(r->axis_x, r->axis_y, r->axis_z);
	const vector_t axis = vector_unit(&v);
	return matrix_rotation(&axis, r->angle);
}

matrix_t matrix_from_scaling(const uniform_scaling_t* us) {
	return matrix_uniform_scaling(us->factor);
}

matrix_t matrix_create(const transformation_t* t) {
	matrix_t result = {0};
	switch (t->type) {
		case TRANSLATION:
			result = matrix_from_translation(&t->translation);
			break;
		case ROTATION:
			result = matrix_from_rotation(&t->rotation);
			break;
		case UNIFORM_SCALING:
			result = matrix_from_scaling(&t->uniform_scaling);
			break;
	};
	return result;
}

matrix_t matrix_translation(const vector_t* displacement) {
	matrix_t r = matrix_identity;
	r.e30 = displacement->x;
	r.e31 = displacement->y;
	r.e32 = displacement->z;
	return r;
}

matrix_t matrix_rotation(const vector_t* axis, double angle) {
	matrix_t r = matrix_identity;
	double s = sin(angle), c = cos(angle);
	double k = 1.0 - c;
	double tk, ts;

	r.e00 = c + axis->x * axis->x * k;
	r.e11 = c + axis->y * axis->y * k;
	r.e22 = c + axis->z * axis->z * k;

	tk = axis->x * axis->y * k;
	ts = axis->z * s;
	r.e01 = tk + ts;
	r.e10 = tk - ts;

	tk = axis->x * axis->z * k;
	ts = axis->y * s;
	r.e02 = tk - ts;
	r.e20 = tk + ts;

	tk = axis->y * axis->z * k;
	ts = axis->x * s;
	r.e12 = tk + ts;
	r.e21 = tk - ts;

	return r;
}

matrix_t matrix_uniform_scaling(double factor) {
	matrix_t r = matrix_identity;
	r.e00 = r.e11 = r.e22 = factor;
	return r;
}

matrix_t matrix_inv(const matrix_t* m) {
	matrix_t r;
	double d
		= m->e03 * m->e12 * m->e21 * m->e30 - m->e02 * m->e13 * m->e21 * m->e30 - m->e03 * m->e11 * m->e22 * m->e30
			+ m->e01 * m->e13 * m->e22 * m->e30
			+ m->e02 * m->e11 * m->e23 * m->e30 - m->e01 * m->e12 * m->e23 * m->e30 - m->e03 * m->e12 * m->e20 * m->e31
			+ m->e02 * m->e13 * m->e20 * m->e31
			+ m->e03 * m->e10 * m->e22 * m->e31 - m->e00 * m->e13 * m->e22 * m->e31 - m->e02 * m->e10 * m->e23 * m->e31
			+ m->e00 * m->e12 * m->e23 * m->e31
			+ m->e03 * m->e11 * m->e20 * m->e32 - m->e01 * m->e13 * m->e20 * m->e32 - m->e03 * m->e10 * m->e21 * m->e32
			+ m->e00 * m->e13 * m->e21 * m->e32
			+ m->e01 * m->e10 * m->e23 * m->e32 - m->e00 * m->e11 * m->e23 * m->e32 - m->e02 * m->e11 * m->e20 * m->e33
			+ m->e01 * m->e12 * m->e20 * m->e33
			+ m->e02 * m->e10 * m->e21 * m->e33 - m->e00 * m->e12 * m->e21 * m->e33 - m->e01 * m->e10 * m->e22 * m->e33
			+ m->e00 * m->e11 * m->e22 * m->e33;

	r.e00 = (m->e12 * m->e23 * m->e31 - m->e13 * m->e22 * m->e31 + m->e13 * m->e21 * m->e32 - m->e11 * m->e23 * m->e32
		- m->e12 * m->e21 * m->e33 + m->e11 * m->e22 * m->e33) / d;
	r.e01 = (m->e03 * m->e22 * m->e31 - m->e02 * m->e23 * m->e31 - m->e03 * m->e21 * m->e32 + m->e01 * m->e23 * m->e32
		+ m->e02 * m->e21 * m->e33 - m->e01 * m->e22 * m->e33) / d;
	r.e02 = (m->e02 * m->e13 * m->e31 - m->e03 * m->e12 * m->e31 + m->e03 * m->e11 * m->e32 - m->e01 * m->e13 * m->e32
		- m->e02 * m->e11 * m->e33 + m->e01 * m->e12 * m->e33) / d;
	r.e03 = (m->e03 * m->e12 * m->e21 - m->e02 * m->e13 * m->e21 - m->e03 * m->e11 * m->e22 + m->e01 * m->e13 * m->e22
		+ m->e02 * m->e11 * m->e23 - m->e01 * m->e12 * m->e23) / d;

	r.e10 = (m->e13 * m->e22 * m->e30 - m->e12 * m->e23 * m->e30 - m->e13 * m->e20 * m->e32 + m->e10 * m->e23 * m->e32
		+ m->e12 * m->e20 * m->e33 - m->e10 * m->e22 * m->e33) / d;
	r.e11 = (m->e02 * m->e23 * m->e30 - m->e03 * m->e22 * m->e30 + m->e03 * m->e20 * m->e32 - m->e00 * m->e23 * m->e32
		- m->e02 * m->e20 * m->e33 + m->e00 * m->e22 * m->e33) / d;
	r.e12 = (m->e03 * m->e12 * m->e30 - m->e02 * m->e13 * m->e30 - m->e03 * m->e10 * m->e32 + m->e00 * m->e13 * m->e32
		+ m->e02 * m->e10 * m->e33 - m->e00 * m->e12 * m->e33) / d;
	r.e13 = (m->e02 * m->e13 * m->e20 - m->e03 * m->e12 * m->e20 + m->e03 * m->e10 * m->e22 - m->e00 * m->e13 * m->e22
		- m->e02 * m->e10 * m->e23 + m->e00 * m->e12 * m->e23) / d;

	r.e20 = (m->e11 * m->e23 * m->e30 - m->e13 * m->e21 * m->e30 + m->e13 * m->e20 * m->e31 - m->e10 * m->e23 * m->e31
		- m->e11 * m->e20 * m->e33 + m->e10 * m->e21 * m->e33) / d;
	r.e21 = (m->e03 * m->e21 * m->e30 - m->e01 * m->e23 * m->e30 - m->e03 * m->e20 * m->e31 + m->e00 * m->e23 * m->e31
		+ m->e01 * m->e20 * m->e33 - m->e00 * m->e21 * m->e33) / d;
	r.e22 = (m->e01 * m->e13 * m->e30 - m->e03 * m->e11 * m->e30 + m->e03 * m->e10 * m->e31 - m->e00 * m->e13 * m->e31
		- m->e01 * m->e10 * m->e33 + m->e00 * m->e11 * m->e33) / d;
	r.e23 = (m->e03 * m->e11 * m->e20 - m->e01 * m->e13 * m->e20 - m->e03 * m->e10 * m->e21 + m->e00 * m->e13 * m->e21
		+ m->e01 * m->e10 * m->e23 - m->e00 * m->e11 * m->e23) / d;

	r.e30 = (m->e12 * m->e21 * m->e30 - m->e11 * m->e22 * m->e30 - m->e12 * m->e20 * m->e31 + m->e10 * m->e22 * m->e31
		+ m->e11 * m->e20 * m->e32 - m->e10 * m->e21 * m->e32) / d;
	r.e31 = (m->e01 * m->e22 * m->e30 - m->e02 * m->e21 * m->e30 + m->e02 * m->e20 * m->e31 - m->e00 * m->e22 * m->e31
		- m->e01 * m->e20 * m->e32 + m->e00 * m->e21 * m->e32) / d;
	r.e32 = (m->e02 * m->e11 * m->e30 - m->e01 * m->e12 * m->e30 - m->e02 * m->e10 * m->e31 + m->e00 * m->e12 * m->e31
		+ m->e01 * m->e10 * m->e32 - m->e00 * m->e11 * m->e32) / d;
	r.e33 = (m->e01 * m->e12 * m->e20 - m->e02 * m->e11 * m->e20 + m->e02 * m->e10 * m->e21 - m->e00 * m->e12 * m->e21
		- m->e01 * m->e10 * m->e22 + m->e00 * m->e11 * m->e22) / d;

	return r;
}

matrix_t matrix_mul(const matrix_t* a, const matrix_t* b) {
	matrix_t r = {0};
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			double e = 0.0;
			for (int k = 0; k < 4; ++k) {
				e += a->e[i][k] * b->e[k][j];
			}
			r.e[i][j] = e;
		}
	}
	return r;
}

matrix_t matrix_transfromation_at(const matrix_t* transformation, const vector_t* position) {
	const matrix_t b = matrix_translation(position);
	const vector_t displacement = vector_neg(position);
	const matrix_t a = matrix_translation(&displacement);
	const matrix_t mul = matrix_mul(&a, transformation);
	return matrix_mul(&mul, &b);
}