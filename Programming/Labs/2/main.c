#include <stdio.h>

#include "matrix.h"
#include "gauss.h"

int main()
{
	Matrix* m = scan_matrix(stdin);
	if (m == NULL) {
		fprintf(stderr, "Matrix read is failed.\n");
		return -1;
	}

	Matrix* result = create_matrix(get_height_matrix(m), 1);
	solve_gauss(m, result);
	print_matrix(stdout, result);

	free_matrix(result);
	free_matrix(m);

	return 0;	
}