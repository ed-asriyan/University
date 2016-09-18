#include <stdio.h>

#include "matrix.h"

int main()
{
	Matrix* m = scan_matrix(stdin);
	if (m == NULL) {
		fprintf(stderr, "Matrix read is failed.\n");
		return -1;
	}
	return 0;	
}