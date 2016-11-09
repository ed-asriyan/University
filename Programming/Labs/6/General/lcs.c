//
// Created by ed on 09.11.16.
//

#include "lcs.h"

LCS* create_lcs(int width, int height) {
	LCS* lcs = (LCS*) malloc(sizeof(LCS));

	lcs->matrix = (int**) malloc(sizeof(int*) * (height + 1));
	lcs->directions = (Direction**) malloc(sizeof(Direction*) * (height + 1));

	for (int i = 0; i <= height; ++i) {
		lcs->matrix[i] = (int*) malloc(sizeof(int) * (width + 1));
		lcs->directions[i] = (Direction*) malloc(sizeof(Direction) * (width + 1));
	}

	lcs->height = height;
	lcs->width = width;

	return lcs;
}

void free_lcs(LCS* lcs) {
	for (int i = 0; i <= lcs->height; ++i) {
		free(lcs->matrix[i]);
		free(lcs->directions[i]);
	}
	free(lcs->matrix);
	free(lcs->directions);

	lcs->matrix = NULL;
	lcs->directions = NULL;
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

const Direction** get_lcs_directions(LCS* lcs) {
	return (const Direction**) lcs->directions;
}
