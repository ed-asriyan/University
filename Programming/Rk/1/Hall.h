//
// Created by ed on 26.10.16.
//

#ifndef CINEMA_HALL_H
#define CINEMA_HALL_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	int **places;

	int size;
} Hall;

Hall* create_hall(int n);

void free_hall(Hall*);

void set_reserved_place(Hall* hall, int x, int y);

void set_favorite_place(Hall* hall, int favorite_x, int favorite_y);

void print_hall(Hall* hall, FILE* out);

#endif //CINEMA_HALL_H
