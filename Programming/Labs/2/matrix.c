#include "matrix.h"

// set the new matrix size
// if operation completed returns 0
// in another way returns -1
int set_size_matrix(Matrix* matrix, int height, int width)
{
	if (height < 0 || width < 0) {
		fprintf(stderr, "set_matrix_size: size is negative (%d, %d)\n", height, width);
		return -1;
	}

	int init_height = matrix->height;
	int init_width = matrix->width;
	double** init_data = matrix->data;

	if (!height || !width) {
		matrix->width = 0;
		matrix->height = 0;

		if (init_data != NULL) {
			if (init_width) {
				for (int i = 0; i < init_height; ++i) {
					free(init_data[i]);
				}
			}
			if (init_height) {
				free(init_data);
			}

			matrix->data = NULL;
		}

		return 0;
	}

	double** new_data = init_data;
	if (init_height != height) {
		matrix->height = height;
		new_data = matrix->data = (double**)realloc(matrix->data, sizeof(double*) * height);
	}
	if (init_width != width) {
		matrix->width = width;
		for (int i = 0; i < height; ++i) {
			new_data[i] = (double*)realloc(new_data[i], sizeof(double) * width);
		}
	}

	return 0;
}

// returns pointer to the new Matrix object
// if input values is out of range returns NULL
Matrix* create_matrix(int height, int width)
{
	if (height < 0 || width < 0) {
		return NULL;
	}

	Matrix* result = (Matrix*)malloc(sizeof(Matrix));
	result->data = NULL;

	set_size_matrix(result, height, width);
	

	return result;
}

// destroys the Matrix object
void free_matrix(Matrix* matrix)
{
	set_size_matrix(matrix, 0, 0);
	free(matrix);
}

// returns pointer to the new Matrix object,
// which is read from input_stream
// if reading is failed returns NULL
Matrix* scan_matrix(FILE* input_stream)
{
	int height;
	fscanf(input_stream, "%d", &height);
	int width = height + 1;

	Matrix* result = (Matrix*)malloc(sizeof(Matrix));
	result->data = NULL;
	set_size_matrix(result, height, width);

	double** data = result->data;

	int is_fail = 0;
	for (int i = 0; i < height; ++i) {
		if (is_fail) {
			break;
		}

		for (int j = 0; j < width; ++j) {
			if (is_fail) {
				break;
			}
			if ((is_fail = (fscanf(input_stream, "%lf", data[i] + j) != 1))) {
				fprintf(stderr, "Error reading stream (invalid value or EOF) in %d row, %d column\n", i, j);
			}
		}
	}

	if (is_fail) {
		free_matrix(result);
		result = NULL;
	}

	return result;
}

// prints the matrix into output_stream
void print_matrix(FILE* output_stream, Matrix* matrix)
{
	int height = matrix->height;
	int width = matrix->width;
	double** data = matrix->data;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			fprintf(output_stream, "%7.3lf ", data[i][j]);
		}
		fprintf(output_stream, "\n");
	}
}

// returns pointer to two-dimensional array
// which represents a matrix
double** get_data_matrix(Matrix* matrix)
{
	return matrix->data;
}

// returns matrix height
int get_height_matrix(Matrix* matrix)
{
	return matrix->height;
}

// returns matrix width
int get_width_matrix(Matrix* matrix)
{
	return matrix->width;
}