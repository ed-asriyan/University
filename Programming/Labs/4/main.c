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

	List list = create_list();

	to_list(&list, f);
	fclose(f);

	print(&list);

	FILE* out = fopen("out.txt", "w");
	to_file(&list, out);
	fclose(out);

	FILE* reversed = fopen("reversed.txt", "w");
	reverse(&list);
	to_file(&list, reversed);
	fclose(reversed);

	FILE* sorted = fopen("sorted.txt", "w");
	sort(&list, string_comparator);
	to_file(&list, sorted);
	fclose(sorted);

	clear(&list);

	return 0;
}