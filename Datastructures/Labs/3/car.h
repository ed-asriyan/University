#ifndef MSTRUCT_H
#define MSTRUCT_H

#include <stdio.h>
#include <stdlib.h>

#include "mio.h"

#define STR_LEN 51
#define MALLOC_STEP 25

struct Car {
	char model[STR_LEN];
	char country[STR_LEN];
	int price;
	char color[STR_LEN];
	int used;

	union {
		struct {
			int warranty;
		} new_car;

		struct {
			int year;
			int mileage;
			int repairs_count;
		} used_car;
	} united;
};

int input_car(struct Car* ms);

void print_car(const struct Car* ms);

int cmp_car(const void* ms1, const void* ms2);

struct CarTable {
	struct Car* ptr_first;
	int n;
	int n_max;
};

int remove_from_car_table(struct CarTable* mt, int num);

void clear_car_table(struct CarTable* mt);

int load_car_table_from_file(struct CarTable* mt, const char* file_name);

int save_car_table_to_file(const struct CarTable* mt, const char* file_name);

int add_to_car_table(struct CarTable* mt, const struct Car* ms);

void print_car_table(const struct CarTable* mt);

void sort_car_table(struct CarTable* mt);

struct Key {
	int key;
	int id;
};

struct KeyTable {
	struct Key* ptr_first;
	int n;
};

int create_key_table(struct CarTable* mt, struct KeyTable* mk);

void clear_key_table(struct KeyTable* mk);

void sort_key_table(struct KeyTable* mk);

void print_key_table(const struct KeyTable* mk);

int print_car_table_by_key(const struct CarTable* mt, const struct KeyTable* mk);

int cmp_key(const void* mk1, const void* mk2);

#endif