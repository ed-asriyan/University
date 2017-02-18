#include <stdlib.h>
#include <string.h>
#include "matrix.h"

int main(int argc, char** argv)
{
    FILE* fin;

    double** matrix = NULL;

    int n, k;

    fin = fopen(argv[1], "r");
    if (!fin)
    {
        printf("Input file error");
        return -1;
    }

    fscanf(fin, "%d %d", &n, &k);

    matrix = allocate_matrix_solid(n, k);

    read_matrix(matrix, n, k, fin);
    double* average = malloc(n * sizeof(double));
    if (average == NULL)
    {
        printf("malloc error");
        free(matrix);
        return -1;
    }
    for (int i = 0; i < n; i++)
    {
        double t = 0;
        for (int j = 0; j < k; j++)
        {
            t += matrix[i][j];
        }
        average[i] = t / k;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
            printf(" %3.1f", matrix[i][j]);
        printf("\n");
    }
    for (int i = 0; i < n; i++)
    {
        printf("%f ", average[i]);
    }

    free(average);
    free(matrix);
    fclose(fin);

    getchar();

    return 0;
}

