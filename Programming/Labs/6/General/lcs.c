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

const int** get_lcs_matrix(const LCS* lcs) {
	return (const int**) lcs->matrix;
}

const Direction** get_lcs_directions(const LCS* lcs) {
	return (const Direction**) lcs->directions;
}

LCS* calc_lcs(const char* X, const char* Y) {
	int x_length = (int) strlen(X);
	int y_length = (int) strlen(Y);

	LCS* lcs = create_lcs(x_length + 1, y_length + 1);

	for (int i = 0; i <= x_length; ++i) {
		lcs->matrix[i][0] = 0;
	}

	for (int j = 0; j <= y_length; ++j) {
		lcs->matrix[0][j] = 0;
	}

	for (int i = 1; i <= x_length; ++i) {
		for (int j = 1; j <= y_length; ++j) {
			if (X[i - 1] == Y[j - 1]) {
				lcs->matrix[i][j] = lcs->matrix[i - 1][j - 1] + 1;
				lcs->directions[i][j] = RIGHTDOWN;
			} else if (lcs->matrix[i - 1][j] >= lcs->matrix[i][j - 1]) {
				lcs->matrix[i][j] = lcs->matrix[i - 1][j];
				lcs->directions[i][j] = DOWN;
			} else {
				lcs->matrix[i][j] = lcs->matrix[i][j - 1];
				lcs->directions[i][j] = RIGHT;
			}
		}
	}

	return lcs;
}
