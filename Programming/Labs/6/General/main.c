//
// Created by ed on 09.11.16.
//

#include <stdio.h>

#include "lcs.h"

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

int main() {
	const char* X = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
	const char* Y = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";

	printf("Source strings:\n");
	printf(" X = %s\n", X);
	printf(" Y = %s\n", Y);
	printf("\n");

	LCS* lcs = calc_lcs(X, Y);

	printf("LCS matrix:\n");
	print_lcs_matrix(lcs);

	printf("LCS directions matrix:\n");
	print_lcs_direction_matrix(lcs);

	printf("Result: ");
	print_lcs(lcs, X, get_lcs_height(lcs), get_lcs_width(lcs));
	fprintf(stdout, "\n");

	free_lcs(lcs);

	return 0;
}