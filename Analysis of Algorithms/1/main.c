#include <stdio.h>

#include "levenshtein.h"

#define BUFFER_SIZE 128

int main() {
	char source[BUFFER_SIZE];
	char dst[BUFFER_SIZE];

	printf("First  string: ");
	scanf("%s", source);
	printf("Second  string: ");
	scanf("%s", dst);

	printf("Distance: %d\n", calc_levenshtein_general(source, dst));

	return 0;
}