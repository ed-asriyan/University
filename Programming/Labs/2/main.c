//
// Created by ed on 10/5/16.
//

#include <stdio.h>

#include "Matrix/matrix.h"
#include "gauss.h"
#include "iterations.h"

int main() {
	// reading the matrix size
	int n = 0;
	scanf("%d", &n);


	// creating matrixes for solving
	Matrix* matrix_gauss = create_matrix(n, n + 1);
	if (matrix_gauss == NULL) {
		fprintf(stderr, "main: creating matrix for gauss method is failed.\n");
		return -11;
	}

	Matrix* matrix_iterations = create_matrix(n, n + 1);
	if (matrix_iterations == NULL) {
		fprintf(stderr, "main: creating matrix for iterations method is failed.\n");
		return -11;
	}


	// reading matrix(es)
	double** matrix_gauss_data = get_data_matrix(matrix_gauss);
	double** matrix_iterations_data = get_data_matrix(matrix_iterations);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j <= n; ++j) {
			double elem = 0;
			scanf("%lf", &elem);

			matrix_gauss_data[i][j] = elem;
			matrix_iterations_data[i][j] = elem;
		}
	}


	// solving by gauss method
	printf("\nGauss method result:\n");
	Matrix* result_gauss = create_matrix(get_height_matrix(matrix_gauss), 1);
	if (result_gauss == NULL) {
		fprintf(stderr, "main: Result matrix creating is failed\n");
		return -10;
	}

	if (!solve_gauss(matrix_gauss, result_gauss)) {
		if (get_height_matrix(result_gauss)) {
			print_matrix(stdout, result_gauss);
		} else {
			printf("There aren't any solutions.\n");
		}
	} else {
		printf("Solving error\n");
	}


	// solving by iterations method
	printf("\nIterations method result:\n");
	Matrix* result_iterations = create_matrix(get_height_matrix(matrix_gauss), 1);
	if (result_iterations == NULL) {
		printf("main: result matrix creating is failed\n");
		return -10;
	}

	if (!solve_iterations(matrix_iterations, result_iterations, 1000, 1e-3)) {
		if (get_height_matrix(result_iterations)) {
			print_matrix(stdout, result_iterations);
		} else {
			printf("There aren't any solutions.\n");
		}
	} else {
		printf("Solving error\n");
	}

	free_matrix(result_iterations);
	free_matrix(result_gauss);
	free_matrix(matrix_iterations);
	free_matrix(matrix_gauss);

	return 0;
}