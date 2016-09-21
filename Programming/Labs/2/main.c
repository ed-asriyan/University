#include <stdio.h>

#include "matrix.h"
#include "gauss.h"

int main()
{
	Matrix* m = scan_matrix(stdin);
	if (m == NULL) {
		fprintf(stderr, "main: Matrix read is failed.\n");
		return -11;
	}

	Matrix* result = create_matrix(get_height_matrix(m), 1);
	
	if (result == NULL) {
		fprintf(stderr, "main: Result matrix creating is failed\n");
		return -10;
	}

	int result_code;
	if (!(result_code = solve_gauss(m, result))) {
		if (get_height_matrix(result)) {
			print_matrix(stdout, result);
		} else {
			printf("There aren't any solutions.\n");
		}
	} else {
		fprintf(stderr, "main: Solving equation by Gauss method is failed\n");
	}

	free_matrix(result);
	free_matrix(m);

	return result_code;	
}