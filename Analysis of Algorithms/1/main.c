#include <stdio.h>

#include "levenshtein.h"

#define BUFFER_SIZE 128

int main() {
	char source[BUFFER_SIZE];
	char dst[BUFFER_SIZE];

	printf("First string  : ");
	scanf("%s", source);
	printf("Second  string: ");
	scanf("%s", dst);

	printf("\n");
	printf("General: %d\n", calc_levenshtein_general(source, dst));
	printf("Recoursive: %d\n", calc_levenshtien_recoursive(source, dst));

	return 0;
}
