//
// Created by ed on 09.11.16.
//

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "double_checker.h"

void read_str(FILE* f, char** str) {
	size_t count;
	getline(str, &count, f);
	(*str)[strlen(*str) - 1] = '\0';
}

int main(int argc, char* argv[]) {
	char* file_name = NULL;
	if (argc == 2) {
		file_name = (char*) malloc(sizeof(char) * strlen(argv[1]));
		strcpy(file_name, argv[1]);
	} else {
		printf("Enter file name (empty for stdin): ");
		read_str(stdin, &file_name);
	}

	FILE* f = NULL;
	if (strlen(file_name)) {
		f = fopen(file_name, "r");
	} else {
		f = stdin;
	}

	if (f != NULL) {
		while (!feof(f)) {
			char* str = NULL;
			read_str(f, &str);
			printf("%s is ", str);
			if (!check_double_str(str)) {
				printf("il");
			}
			printf("legal\n");
			free(str);
		}

		fclose(f);
	} else {
		fprintf(stderr, "Error: can not open the file %s.\n", file_name);
	}

	free(file_name);

	return 0;
}