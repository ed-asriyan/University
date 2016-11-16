//
// Created by ed on 09.11.16.
//

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "lcs.h"

/**
 * @brief Generates random string.
 * @param str Pointer to the string to generate.
 * @param length Length of the string.
 */
void generate_random_string(char* str, int length) {
	const char min_char = 'A';
	const char max_char = 'Z';

	for (int i = 0; i < length; ++i) {
		str[i] = (char) (rand() % ((int) max_char + 1 - (int) min_char) + (int) min_char);
	}
	str[length] = '\0';
}

/**
 * @brief Converts direction to human-like character.
 * @param direction The direction to convert.
 * @return Human-like character.
 */
char direction_to_char(Direction direction) {
	switch (direction) {
		case DOWN: return '|';
		case RIGHT: return '-';
		case RIGHTDOWN: return '\\';
	}
	return '0';
}

/**
 * @brief Prints to the stdout the resultive LCS string.
 * @param lcs Pointer to LCS instance.
 * @param str Source string.
 * @param i LCS matrix height.
 * @param j LCS matrix width.
 */
void print_lcs(const LCS* lcs, const char* str, int i, int j) {
	if (i == 0 || j == 0) {
		return;
	}
	if (lcs->directions[i][j] == RIGHTDOWN) {
		print_lcs(lcs, str, i - 1, j - 1);
		printf("%c", str[i - 1]);
	} else if (lcs->directions[i][j] == DOWN) {
		print_lcs(lcs, str, i - 1, j);
	} else {
		print_lcs(lcs, str, i, j - 1);
	}
}

/**
 * @brief Prints to the stdout the LCS direction matrix in human-like view.
 * @param lcs Pointer to LCS instance.
 */
void print_lcs_direction_matrix(const LCS* lcs) {
	int height = get_lcs_height(lcs);
	int width = get_lcs_width(lcs);
	const Direction** directions = get_lcs_directions(lcs);

	for (int i = 1; i <= height; ++i) {
		for (int j = 1; j <= width; ++j) {
			printf("%2c", direction_to_char(directions[i][j]));
		}
		printf("\n");
	}
	printf("\n");
}

/**
 * @brief Prints to the stdout the LCS matrix.
 * @param lcs Pointer to LCS instance.
 */
void print_lcs_matrix(const LCS* lcs) {
	int height = get_lcs_height(lcs);
	int width = get_lcs_width(lcs);
	const int** matrix = get_lcs_matrix(lcs);

	for (int i = 0; i <= height; ++i) {
		for (int j = 0; j <= width; ++j) {
			printf("%3d", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/**
 * @brief Reads a whole line from stdin.
 * @param str Pointer to string to allocate and write in.
 */
void scan_line(char** str) {
	size_t length;
	getline(str, &length, stdin);
	(*str)[strlen(*str) - 1] = '\0';
}

int main(int argc, const char* argv[]) {
	int length = 1001;

	if (argc == 2) {
		length = atoi(argv[1]);
	}

	char* x = (char*) malloc(sizeof(char) * length + 1);
	char* y = (char*) malloc(sizeof(char) * length);

	srand((unsigned int) time(NULL));
	generate_random_string(x, length);
	generate_random_string(y, length - 1);

	printf("Source strings:\n");
	printf(" X = %s\n", x);
	printf(" Y = %s\n", y);
	printf("\n");

	LCS* lcs = calc_lcs(x, y);

	printf("Result: ");
	print_lcs(lcs, x, get_lcs_height(lcs), get_lcs_width(lcs));
	printf("\n");

	free_lcs(lcs);

	free(y);
	free(x);

	return 0;
}