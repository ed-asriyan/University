#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double** allocate_matrix_solid(int n, int k);
void read_matrix(double** data, int n, int k, FILE* fin);

#endif // MATRIX_H

