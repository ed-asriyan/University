//
// Created by ed on 09.11.16.
//

#include "lcs.h"

LCS* create_lcs(int width, int height) {
	LCS* lcs = (LCS*) malloc(sizeof(LCS));

	lcs->matrix = (int**) malloc(sizeof(int*) * (height + 1));
	lcs->symbols = (char**) malloc(sizeof(char*) * (height + 1));

	for (int i = 0; i <= height; ++i) {
		lcs->matrix[i] = (int*) malloc(sizeof(int) * (width + 1));
		lcs->symbols[i] = (char*) malloc(sizeof(char) * (width + 1));
	}

	lcs->height = height;
	lcs->width = width;

	return lcs;
}

void free_lcs(LCS* lcs) {
	for (int i = 0; i <= lcs->height; ++i) {
		free(lcs->matrix[i]);
		free(lcs->symbols[i]);
	}
	free(lcs->matrix);
	free(lcs->symbols);

	lcs->matrix = NULL;
	lcs->symbols = NULL;
	lcs->height = 0;
	lcs->width = 0;

	free(lcs);
}

int get_lcs_height(const LCS* lcs) {
	return lcs->height;
}

int get_lcs_width(const LCS* lcs) {
	return lcs->width;
}

const int** get_lcs_matrix(LCS* lcs) {
	return (const int**) lcs->matrix;
}

const char** get_lcs_symbols(LCS* lcs) {
	return (const char**) lcs->symbols;
}
