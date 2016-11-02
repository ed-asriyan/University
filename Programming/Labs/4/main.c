#include <stdio.h>

#include "LinkedList.h"

#define NOT_ENOUGH_ARGUMENTS 0
#define INVALID_ARGUMENT     0

#define OUT_FILE "out.txt"
#define REVERSED_FILE "reversed.txt"
#define SORTED_FILE "sorted.txt"

int reverse_list(const char* file_name, List* list) {
	FILE* reversed = fopen(REVERSED_FILE, "w");
	if (reversed == NULL) {
		return 0;
	}
	reverse(list);
	to_file(list, reversed);
	fclose(reversed);
}

int sort_list(const char* file_name, List* list) {
	FILE* sorted = fopen(SORTED_FILE, "w");
	if (sorted == NULL) {
		return 0;
	}
	sort(list, string_comparator);
	to_file(list, sorted);
	fclose(sorted);
}

int file(const char* file_name, List* list) {
	FILE* out = fopen("out.txt", "w");
	if (out == NULL) {
		return 0;
	}
	to_file(list, out);
	fclose(out);
}

int main(const int argc, const char** argv) {
	FILE* f = NULL;
	while (f == NULL) {
		char file_name[1024];
		if (argc >= 2) {
			f = fopen(argv[1], "r");
		} else { ;
			printf("Enter file name: ");
			scanf("%s", file_name);
		}

		if (f == NULL) {
			printf("Can not open the file.\n\n");
		}
	}

	List list = create_list();
	to_list(&list, f);
	fclose(f);
	printf("\nLoad successful\n\n");

	int choose = 0;
	do {
		printf("~~ Menu ~~\n");
		printf("1 - print list to stdout\n");
		printf("2 - print list to file\n");
		printf("3 - print sorted list to file\n");
		printf("4 - print reversed list to file\n");
		printf("0 - exit\n");

		scanf("%d", &choose);
		switch (choose) {
			case 1: print(&list);
				break;
			case 2:
				if (!file(SORTED_FILE, &list)) {
					printf("\nSuccessful.\n\n");
				} else {
					printf("\nFailed.\n\n");
				}
				break;
			case 3:
				if (!sort_list(SORTED_FILE, &list)) {
					printf("\nSuccessful.\n\n");
				} else {
					printf("\nFailed.\n\n");
				}
				break;
			case 4:
				if (!reverse_list(REVERSED_FILE, &list)) {
					printf("\nSuccessful.\n\n");
				} else {
					printf("\nFailed.\n\n");
				}
				break;
			default: break;
		}

	} while (choose);

	clear(&list);

	return 0;
}