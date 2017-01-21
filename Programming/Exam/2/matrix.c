#include "matrix.h"

double** allocate_matrix_solid(int n, int k)
{
    double **data = malloc(n * sizeof(double*) +
                              n * k * sizeof(double));
    if (!data)
        return NULL;

    for (int i = 0; i < n; i++)
        data[i] = (double*)((char*) data +
                          n * sizeof(double*) +
                                  i * k * sizeof(double));
    return data;
}

void read_matrix(double** data, int n, int k, FILE* fin)
{
    assert(fin);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < k; j++)
            fscanf(fin, "%lf", &data[i][j]);
}

