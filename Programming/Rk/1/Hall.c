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

int calc_lucky_sum(Hall* hall, int count) {
	int** places = hall->places;
	int n = hall->size;

	int** best_places = (int**) malloc(sizeof(int*) * n);
	int best_places_count = 0;

	for (int i = 0; i < n; ++i) {
		int free_count = 0;
		for (int j = 0; j < n; ++j) {
			if (free_count == count) {
				best_places[best_places_count++] = *(places + i) + j;
				free_count = 0;
			} else {
				if (places[i][j] < 0) {
					free_count = 0;
				} else {
					++free_count;
				}
			}
		}
	}

	int the_best_sum = -1;
	for (int i = 0; i < best_places_count; ++i) {
		int sum = 0;
		for (int j = 0; j < count; ++j) {
			sum += best_places[i][j];
		}
		if (the_best_sum < 0 || sum < the_best_sum) {
			the_best_sum = sum;
		}
	}

	free(best_places);
	return the_best_sum;
}
