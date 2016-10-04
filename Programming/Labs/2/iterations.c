//
// Created by ed on 10/5/16.
//

#include "iterations.h"

void FreeData(double* a, double* b, double* c, double* d) {
	free(a);
	free(b);
	free(c);
	free(d);
}

int solve_iterations(Matrix* a, Matrix* result, int iter_count, double epsilon) {
	if (iter_count <= 0) {
		fprintf(stderr, "solve_iterations: iteration count must be positive\n");
		return -1;
	}
	if (epsilon <= 0) {
		fprintf(stderr, "solve_iterations: epsilon must be positive\n");
		return -1;
	}

	int a_height = a->height;
	int a_width = a->width;

	if (a_height + 1 != a_width) {
		fprintf(stderr, "solve_gauss: unsupported matrix (a) size: %dx%d", a_height, a_width);
		return -1;
	}

	double** a_data = a->data;

	double buf_c;
	double* curr_x = (double*) malloc(sizeof(double) * a_height);
	double* prev_x = (double*) malloc(sizeof(double) * a_height);
	double* temp_x = (double*) malloc(sizeof(double) * a_height);
	double* buf_row = (double*) malloc(sizeof(double) * (a_width));

	for (int i = 0; i < a_height; i++) {
		curr_x[i] = 0;
		prev_x[i] = 0;
		temp_x[i] = 0;
	}

	for (int i = 0; i < a_height; i++) {
		buf_c = a_data[i][i];
		for (int j = 0; j < (a_width); j++) {

			if (i == j) {
				a_data[i][j] = 0;
			} else {
				a_data[i][j] /= -buf_c;
			}
			if (j == a_height) {
				a_data[i][j] *= -1;
			}
		}
	}

	double euclid_norm = 0;

	for (int i = 0; i < a_height; i++) {
		for (int j = 0; j < a_height; j++) {
			euclid_norm += a_data[i][j] * a_data[i][j];
		}
	}
	euclid_norm = sqrt(euclid_norm);

	if (euclid_norm > 1) {
		fprintf(stderr, "ERROR: INVALID_MATRIX!!!\n");
		FreeData(curr_x, prev_x, temp_x, buf_row);
		return -1;
	}

	double sum = 0;
	int k = 0, max;

	for (int i = 0; i < a_height; i++) {
		prev_x[i] = a_data[i][a_height];
	}

	do {
		k++;
		if (k != 1) {
			for (int i = 0; i < a_height; i++) {
				prev_x[i] = curr_x[i];
			}
		}

		for (int i = 0; i < a_height; i++) {
			sum = 0;
			for (int j = 0; j < a_height; j++) {
				sum += prev_x[j] * a_data[i][j];
			}

			curr_x[i] = sum + a_data[i][a_height];
		}

		max = 0;
		for (int i = 0; i < a_height - 1; i++) {
			if (abs(curr_x[max] - prev_x[max]) < abs(curr_x[i + 1] - prev_x[i + 1])) {
				max = i + 1;
			}
		}

	} while ((abs(curr_x[max] - prev_x[max]) < epsilon) && (k < iter_count));

	free(buf_row);
	free(prev_x);
	free(temp_x);

	set_size_matrix(result, a_height, 1);
	double** result_data = get_data_matrix(result);
	for (int i = 0; i < a_height; ++i) {
		result_data[i][0] = curr_x[i];
	}

	free(curr_x);

	return 0;
}