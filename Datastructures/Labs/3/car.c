#include "car.h"

#include <stdio.h>


// ----- Car -----

void print_car(const struct Car* ms) {
	printf("Car model:         %s\n", ms->model);
	printf("Country:           %s\n", ms->country);
	printf("Price:             %d\n", ms->price);
	printf("Color:             %s\n", ms->color);

	if (ms->used == 0) {
		printf("State:             New\n");
		printf("Warranty (years):  %d\n", ms->united.new_car.warranty);
	} else {
		printf("State:             Used\n");
		printf("Year:              %d\n", ms->united.used_car.year);
		printf("Mileage (km):      %d\n", ms->united.used_car.mileage);
		printf("Repairs count:     %d\n", ms->united.used_car.repairs_count);
	}
}

int input_car(struct Car* ms) {
	if (input_string("Input car model:\n", ms->model, STR_LEN) != 0)
		return -1;

	if (input_string("Input country:\n", ms->country, STR_LEN) != 0)
		return -1;

	if (input_positive_int("Input price:\n", &(ms->price)) != 0)
		return -1;

	if (input_string("Input color:\n", ms->color, STR_LEN) != 0)
		return -1;

	if (input_binary("Input state (0 - new, 1 - used):\n", &(ms->used)) != 0)
		return -1;

	if (ms->used == 0) {
		if (input_positive_int("Input warranty:\n", &(ms->united.new_car.warranty)) != 0)
			return -1;
	} else {
		if (input_positive_int("Input year:\n", &(ms->united.used_car.year)) != 0)
			return -1;

		if (input_positive_int("Input mileage:\n", &(ms->united.used_car.mileage)) != 0)
			return -1;

		if (input_positive_int("Input repairs count:\n", &(ms->united.used_car.repairs_count)) != 0)
			return -1;
	}

	return 0;
}

/*
int save_mstruct_to_file(const struct Car *ms, int n, const char *file_name)
{
    FILE *f = fopen(file_name, "wb");

    if (!f)
        return 1; // Error opening file

    if (fwrite(ms, sizeof(struct Car), n, f) != n)
    {
        fclose(f);
        return 2; // Error writing to file
    }

    fclose(f);
    return 0;
}
*/

// ----- Car ----- end



// ----- CarTable -----

int load_car_table_from_file(struct CarTable* mt, const char* file_name) {
	struct Car ms;
	FILE* f = fopen(file_name, "rb");
	int read_ret = 1;

	if (!f)
		return -1;  // Error opening file

	clear_car_table(mt);

	while (1) {
		read_ret = fread(&ms, sizeof(struct Car), 1, f);
		if (read_ret == 1)
			add_to_car_table(mt, &ms);
		else {
			//printf("\nReading error: %d\n", read_ret);
			break;
		}
	}

	fclose(f);
	return 0;
}

int save_car_table_to_file(const struct CarTable* mt, const char* file_name) {
	FILE* f = fopen(file_name, "wb");

	if (!f)
		return -1; // Error opening file

	if (fwrite(mt->ptr_first, sizeof(struct Car), mt->n, f) != mt->n) {
		fclose(f);
		return -2; // Error writing to file
	}

	fclose(f);
	return 0;
}

void clear_car_table(struct CarTable* mt) {
	mt->n = 0;
	mt->n_max = 0;

	if (mt->ptr_first != NULL) {
		free(mt->ptr_first);
		mt->ptr_first = NULL;
	}
}

int remove_from_car_table(struct CarTable* mt, int num) {
	if (num > 0 && num <= mt->n) {
		mt->ptr_first[num - 1] = mt->ptr_first[mt->n - 1];
		mt->n--;

		return 0;
	} else
		return -1;
}

int add_to_car_table(struct CarTable* mt, const struct Car* ms) {
	if (mt->n >= mt->n_max) {
		struct Car* ptr_free = mt->ptr_first;
		struct Car* ptr_tmp = mt->ptr_first;

		mt->n_max += MALLOC_STEP;

		struct Car* ptr_tmp_new = (struct Car*) malloc(mt->n_max * sizeof(struct Car));

		if (!ptr_tmp_new)
			return -1; // Error in malloc

		mt->ptr_first = ptr_tmp_new;

		for (int i = 0; i < mt->n; i++) {
			*ptr_tmp_new = *ptr_tmp;

			ptr_tmp++;
			ptr_tmp_new++;
		}

		free(ptr_free);
	}

	mt->n++;
	mt->ptr_first[mt->n - 1] = *ms;

	return 0;
}

void print_car_table(const struct CarTable* mt) {
	struct Car* ptr_cur = mt->ptr_first;

	printf("\n### Table ###\n");

	if (mt->n <= 0)
		printf("  Table is empty.\n");
	else {
		printf("--------------------------------------------\n");

		for (int i = 0; i < mt->n; i++) {
			printf("[ Record %d ]\n", (i + 1));
			print_car(ptr_cur);
			printf("--------------------------------------------\n");

			ptr_cur++;
		}
	}

	printf("### Table end ###\n");
}

int cmp_car(const void* ms1, const void* ms2) {
	return ((struct Car*) ms1)->price - ((struct Car*) ms2)->price;
}

void sort_car_table(struct CarTable* mt) {
	qsort(mt->ptr_first, mt->n, sizeof(struct Car), cmp_car);
}

// ----- CarTable ----- end



// ----- KeyTable -----

int create_key_table(struct CarTable* mt, struct KeyTable* mk) {
	struct Car* ptr_s;
	struct Key* ptr_key;

	clear_key_table(mk);

	mk->n = mt->n;

	mk->ptr_first = (struct Key*) malloc(sizeof(struct Key) * mk->n);

	if (mk->ptr_first == NULL)
		return -1; // Error in malloc


	ptr_s = mt->ptr_first;
	ptr_key = mk->ptr_first;

	for (int i = 0; i < mk->n; i++) {
		ptr_key->id = i;
		ptr_key->key = ptr_s->price;

		ptr_key++;
		ptr_s++;
	}

	return 0;
}

void clear_key_table(struct KeyTable* mk) {
	if (mk->ptr_first != NULL) {
		free(mk->ptr_first);
		mk->ptr_first = NULL;
	}

	mk->n = 0;
}

void print_key_table(const struct KeyTable* mk) {
	printf("\n0-n Key table 0-n\n");

	if (mk->n <= 0)
		printf("  Key table is empty.\n");
	else {
		struct Key* ptr_key = mk->ptr_first;

		printf("--------------------------------------------\n");

		for (int i = 0; i < mk->n; i++) {
			printf("ID:   %d\n", ptr_key->id + 1);
			printf("Key:  %d\n", ptr_key->key);
			printf("--------------------------------------------\n");

			ptr_key++;
		}
	}

	printf("0-n Key table end 0-n\n");
}

int print_car_table_by_key(const struct CarTable* mt, const struct KeyTable* mk) {
	struct Key* ptr_key = mk->ptr_first;

	if (mk->n != mt->n)
		return -1; // Different sizes

	printf("\n### Table in key order ###\n");

	if (mt->n <= 0)
		printf("  Table is empty.\n");
	else {
		printf("--------------------------------------------\n");

		for (int i = 0; i < mk->n; i++) {
			if (ptr_key->id<0 || ptr_key->id>(mt->n - 1))
				return -2; // Invalid ID found

			printf("[ Record %d ]\n", (i + 1));
			print_car(&mt->ptr_first[ptr_key->id]);
			printf("--------------------------------------------\n");

			ptr_key++;
		}
	}

	printf("### Table end ###\n");

	return 0;
}

int cmp_key(const void* mk1, const void* mk2) {
	return ((struct Key*) mk1)->key - ((struct Key*) mk2)->key;
}

void sort_key_table(struct KeyTable* mk) {
	qsort(mk->ptr_first, mk->n, sizeof(struct Key), cmp_key);
}

// ----- KeyTable ----- end
