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

// returns the pointer to the elements by int coordinates
// if coordinates is out of range returns NULL
double* get_elem_matrix(Matrix* matrix, int row, int column);

// returns pointer to the new Matrix object,
// which is read from input_stream
// if reading is failed returns NULL
Matrix* scan_matrix(FILE* input_stream);

// prints the matrix into output_stream
void print_matrix(FILE* output_stream, Matrix* matrix);

#endif // __ED_ASRIYAN_MATRIX_H__