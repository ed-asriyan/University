#include "gauss.h"

int solve_gauss(Matrix* a, Matrix* result)
{
	int a_height = get_height_matrix(a);
	int a_width = get_width_matrix(a);

	if (a_height + 1 != a_width) {
		fprintf(stderr, "solve_gauss: unsupported matrix (a) size: %dx%d", a_height, a_width);
		return -1;
	}

	int n = a_height;
	set_size_matrix(result, n, 1);

	double** a_data = get_data_matrix(a);
	double** x_data = get_data_matrix(result);

	for (int k = 1; k < n; ++k) {
		for (int j = k; j < n; ++j) {
			double m = a_data[j][k - 1] / a_data[k - 1][k - 1];
			for (int i = 0; i <= n; ++i) {
				a_data[j][i] -= m * a_data[k - 1][i];
			}
		}
	}
	
	x_data[n - 1][0] = a_data[n - 1][n] / a_data[n - 1][n - 1];
	for (int i = n - 2; i >= 0; --i) {
		double temp = 0;
		for (int j = i + 1; j < n; ++j) {
			temp += a_data[i][j] * x_data[j][0];
		}
		x_data[i][0] = (a_data[i][n] - temp) / a_data[i][i];
	}

	return 0;
}