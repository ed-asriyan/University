#include <stdio.h>

#include "levenshtein/levenshtein.h"

#define BUFFER_SIZE 128

int main() {
	char source[BUFFER_SIZE];
	char dst[BUFFER_SIZE];

	printf("Source string    : ");
	scanf("%s", source);
	printf("Comparable string: ");
	scanf("%s", dst);

	printf("\n");
	printf("General   : %d\n", calc_levenshtein_general(source, dst));
	printf("Modified  : %d\n", calc_levenshtein_modified(source, dst));
	printf("Recoursive: %d\n", calc_levenshtein_recursive(source, dst));

	return 0;
}
