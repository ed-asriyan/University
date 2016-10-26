//
// Created by ed on 26.10.16.
//

#include <stddef.h>

#include "Hall.h"

Hall* create_hall(int n) {
	Hall* result = (Hall*) malloc(sizeof(Hall));
	result->size = n;

	int** places = result->places = (int**) malloc(sizeof(int*) * n);
	for (int i = 0; i < n; ++i) {
		places[i] = (int*) malloc(sizeof(int) * n);
		for (int j = 0; j < n; ++j) {
			places[i][j] = 0;
		}
	}

	return result;
}

void free_hall(Hall* hall) {
	int** places = hall->places;
	int n = hall->size;
	for (int i = 0; i < n; ++i) {
		free(places[i]);
	}
	free(places);
	free(hall);
}

void set_reserved_place(Hall* hall, int x, int y) {
	hall->places[y][x] = -1;
}

void set_favorite_place(Hall* hall, int favorite_x, int favorite_y) {
	int** places = hall->places;
	int n = hall->size;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (places[i][j] >= 0) {
				places[i][j] = abs(i - favorite_y) + abs(j - favorite_x);
			}
		}
	}
}

void print_hall(Hall* hall, FILE* out) {
	int** places = hall->places;
	int n = hall->size;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			fprintf(out, "%3d", places[i][j]);
		}
		fprintf(out, "\n");
	}
}
