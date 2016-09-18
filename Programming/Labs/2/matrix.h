#ifndef __ED_ASRIYAN_MATRIX_H__
#define __ED_ASRIYAN_MATRIX_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
	int height;
	int width;

	double** data;
} Matrix;


// returns pointer to the new Matrix object
// if input values is out of range returns NULL
Matrix* create_matrix(int heigth, int width);

// destroys the Matrix object
void free_matrix(Matrix* matrix);

// set the new matrix size
// if operation completed returns 0
// in another way returns -1
int set_size_matrix(Matrix* matrix, int height, int width);

// returns pointer to two-dimensional array
// which represents a matrix
double** get_data_matrix(Matrix* matrix);

// returns pointer to the new Matrix object,
// which is read from input_stream
// if reading is failed returns NULL
Matrix* scan_matrix(FILE* input_stream);

// prints the matrix into output_stream
void print_matrix(FILE* output_stream, Matrix* matrix);

// returns matrix height
int get_height_matrix(Matrix* matrix);

// returns matrix width
int get_width_matrix(Matrix* matrix);

#endif // __ED_ASRIYAN_MATRIX_H__