#include <stdio.h>

#include "LinkedList.h"

int reverse_list(const char* file_name, List* list) {
	FILE* reversed = fopen(file_name, "w");
	if (reversed == NULL) {
		return 0;
	}
	reverse(list);
	to_file(list, reversed);
	fclose(reversed);
	return 1;
}

int sort_list(const char* file_name, List* list) {
	FILE* sorted = fopen(file_name, "w");
	if (sorted == NULL) {
		return 0;
	}
	sort(list, string_comparator);
	to_file(list, sorted);
	fclose(sorted);
	return 1;
}

int file(const char* file_name, List* list) {
	FILE* out = fopen(file_name, "w");
	if (out == NULL) {
		return 0;
	}
	to_file(list, out);
	fclose(out);
	return 1;
}

int main(const int argc, const char** argv) {
	char file_name[1024];
	FILE* f = NULL;
	while (f == NULL) {
		if (argc >= 2) {
			f = fopen(argv[1], "r");
		} else { ;
			printf("Enter file name: ");
			scanf("%s", file_name);
			f = fopen(file_name, "r");
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

				if (file("list.txt", &list)) {
					printf("\nSuccessful.\n\n");
				} else {
					printf("\nFailed.\n\n");
				}
				break;
			case 3:
					if (sort_list("sorted_list.txt", &list)) {
					printf("\nSuccessful.\n\n");
				} else {
					printf("\nFailed.\n\n");
				}
				break;
			case 4:
				if (reverse_list("reversed_list.txt", &list)) {
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