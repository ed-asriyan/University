#include "matrix.h"

// returns pointer to the new Matrix object
// if input values is out of range returns NULL
Matrix* create_matrix(int height, int width)
{
	if (height < 0 || width < 0) {
		return NULL;
	}

	Matrix* result = (Matrix*)malloc(sizeof(Matrix));

	result->height = height;
	result->width = width;
	double** data = result->data = (double**)malloc(sizeof(double*) * height);
	for (int i = 0; i < height; ++i) {
		data[i] = (double*)calloc(width, sizeof(double));
	}

	return result;
}

// destroys the Matrix object
void free_matrix(Matrix* matrix)
{
	int height = matrix->height;
	double** data = matrix->data;

	for (int i = 0; i < height; ++i) {
		free(data[i]);
	}
	free(data);
	free(matrix);
}

// returns the pointer to the elements by int coordinates
// if coordinates is out of range returns NULL
double* get_elem_matrix(Matrix* matrix, int row, int column)
{
	if (row < 0 || row >= matrix->width ||
		column < 0 || column >= matrix->height) {
		return NULL;
	}

	return matrix->data[row] + column;
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
	result->height = 0;
	result->width = width;
	double** data = result->data = (double**)malloc(sizeof(double*) * height);

	int is_fail = 0;
	for (int i = 0; i < height; ++i) {
		if (is_fail) {
			break;
		}

		data[i] = (double*)malloc(sizeof(double) * width);
		++result->height;

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