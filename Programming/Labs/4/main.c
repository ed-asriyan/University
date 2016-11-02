#include <stdio.h>

#include "LinkedList.h"

#define NOT_ENOUGH_ARGUMENTS 0
#define INVALID_ARGUMENT     0

int main(const int argc, const char** argv) {
	if (argc != 2) {
		fprintf(stderr, "ERROR: NOT_ENOUGH_ARGUMENTS!!!\n");
		return NOT_ENOUGH_ARGUMENTS;
	}

	FILE* f = fopen(argv[1], "r");

	if (!f) {
		fprintf(stderr, "ERROR: INVALID_ARGUMENT!!!\n");
		fclose(f);
		return INVALID_ARGUMENT;
	}

	List list = Constructor();

	ToList(&list, f);
	fclose(f);

	Print(&list);

	FILE* out = fopen("out.txt", "w");
	ToFile(&list, out);
	fclose(out);

	FILE* reversed = fopen("reversed.txt", "w");
	Reverse(&list);
	ToFile(&list, reversed);
	fclose(reversed);

	FILE* sorted = fopen("sorted.txt", "w");
	Sort(&list, string_comparator);
	ToFile(&list, sorted);
	fclose(sorted);

	Clear(&list);

	return 0;
}