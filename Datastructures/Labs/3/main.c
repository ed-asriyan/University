#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "car.h"
#include "mio.h"

struct CarTable table = {NULL, 0, 0};
struct KeyTable key_table = {NULL, 0};

/// \details swaps two values
/// \param[in] a first value
/// \param[in] b second value
/// \param[in] size size of the value
void swap(void* a, void* b, void* buf, size_t size) {
	memcpy(buf, a, size);
	memcpy(a, b, size);
	memcpy(b, buf, size);
}

/// \details sorts the array
/// \param[in] base pointer to the first element of the array
/// \param[in] num number of elements in the array
/// \param[in] size size of the element
/// \param[in] compare pointer to the comparison function
void msort(void* base, size_t num, size_t size,
           int (* compare)(const void*, const void*)) {
	int flag = 1;
	void* cur, * prev, * last;
	void* buf = malloc(size);

	cur = base;
	prev = base;
	last = (void*) ((char*) base + size * (num - 1));

	while (flag) {
		flag = 0;

		while (cur != last) {
			prev = cur;
			cur = (void*) ((char*) cur + size);

			if (compare(cur, prev) < 0) {
				swap(cur, prev, buf, size);
				flag = 1;
			}
		}

		if (!flag)
			break;

		flag = 0;

		while (prev != base) {
			cur = prev;
			prev = (void*) ((char*) prev - size);

			if (compare(cur, prev) < 0) {
				swap(cur, prev, buf, size);
				flag = 1;
			}
		}
	}

	free(buf);
}

void fill_random(struct CarTable* mt) {
	struct Car* cur = mt->ptr_first;
	char color[][STR_LEN] = {"White", "Grey", "Black", "Red", "Blue", "Green"};

	srand((unsigned int) time(NULL));

	for (int i = 0; i < mt->n; i++) {
		cur->used = rand() % 2;

		if (cur->used == 0) {
			cur->price = (1200 + rand() % 800) * 1000;
			cur->united.new_car.warranty = 1 + rand() % 9;
		} else {
			cur->price = (900 + rand() % 500) * 1000;
			cur->united.used_car.mileage = rand() % 50 * 1000;
			cur->united.used_car.year = 1990 + rand() % 25;
			cur->united.used_car.repairs_count = rand() % 4;
		}

		strcpy(cur->color, color[rand() % 6]);

		cur++;
	}
}

unsigned long long tick(void) {
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d));
	return d;
}

void measure_sorting_time(void) {
	char str[STR_LEN];
	struct CarTable tmp_table = {NULL, 0, 0};
	struct KeyTable tmp_key_table = {NULL, 0};
	unsigned long long tm, tms;

	if (input_string("Input file name:\n", str, STR_LEN) == 0) {
		if (load_car_table_from_file(&tmp_table, str) == 0)
			printf("\n{ Successfully loaded }\n");
		else {
			printf("\n{ Unable to load! }\n");
			return;
		}


		// qsort table
		tms = 0;

		for (int i = 0; i < 1000; i++) {
			tm = tick();
			sort_car_table(&tmp_table);
			tm = tick() - tm;
			tms += tm;

			load_car_table_from_file(&tmp_table, str);
		}

		printf("\n{ Table sorting clock cycles (qsort) = %llu }\n", tms);


		// qsort key
		tms = 0;

		for (int i = 0; i < 1000; i++) {
			create_key_table(&tmp_table, &tmp_key_table);

			tm = tick();
			sort_key_table(&tmp_key_table);
			tm = tick() - tm;
			tms += tm;
		}

		printf("\n{ Key table sorting clock cycles (qsort) = %llu }\n", tms);


		// msort table
		tms = 0;

		for (int i = 0; i < 1000; i++) {
			tm = tick();
			msort(tmp_table.ptr_first, tmp_table.n, sizeof(struct Car), cmp_car);
			tm = tick() - tm;
			tms += tm;

			load_car_table_from_file(&tmp_table, str);
		}

		printf("\n{ Table sorting clock cycles (bubble sort) = %llu }\n", tms);


		// msort key
		tms = 0;

		for (int i = 0; i < 1000; i++) {
			create_key_table(&tmp_table, &tmp_key_table);

			tm = tick();
			msort(tmp_key_table.ptr_first, tmp_key_table.n, sizeof(struct Key), cmp_key);
			tm = tick() - tm;
			tms += tm;
		}

		printf("\n{ Key table sorting clock cycles (bubble sort) = %llu }\n", tms);

		printf("\n{ Table size = %ld B }\n", sizeof(struct Car) * tmp_table.n);
		printf("\n{ Key table size = %ld B }\n", sizeof(struct Key) * tmp_key_table.n);
	}
}

void search(void) {
	char str[STR_LEN];
	int found = 0;

	printf("\nSearching for used cars with mileage < 10000 km,\nno repairs and specified color...\n");
	if (input_string("\nInput color to search:\n", str, STR_LEN) == 0) {
		struct Car* ptr_cur = table.ptr_first;

		printf("\n-O Search results -O\n");

		printf("--------------------------------------------\n");

		for (int i = 0; i < table.n; i++) {
			if (strcmp(str, ptr_cur->color) == 0 && ptr_cur->used == 1 &&
				ptr_cur->united.used_car.mileage < 10000 && ptr_cur->united.used_car.repairs_count == 0) {
				printf("[ Record %d ]\n", (i + 1));
				print_car(ptr_cur);
				printf("--------------------------------------------\n");

				found++;
			}

			ptr_cur++;
		}

		if (found == 0) {
			printf("  Nothing found.\n");
			printf("--------------------------------------------\n");
		}

		printf("-O Search results end -O\n");
	}
}

int menu(void) {
	printf("\n~~~ Menu ~~~\n");
	printf("1 - Load from file\n");
	printf("2 - Save to file\n");
	printf("3 - Add record\n");
	printf("4 - Remove record\n");
	printf("5 - Sort table\n");
	printf("6 - Print table\n");
	printf("7 - Create key table\n");
	printf("8 - Sort key table\n");
	printf("9 - Print key table\n");
	printf("10 - Print table in key order\n");
	printf("11 - Search\n");
	printf("12 - Measure sorting time\n");
	printf("0 - Exit\n");

	int choice;
	struct Car ms;

	if (scanf("%d", &choice) == 1) {
		if (choice == 1) // Load
		{
			char str[STR_LEN];

			if (input_string("Input file name:\n", str, STR_LEN) == 0) {
				if (load_car_table_from_file(&table, str) == 0)
					printf("\n{ Successfully loaded }\n");
				else
					printf("\n{ Unable to load! }\n");
			}
		} else if (choice == 2) // Save
		{
			char str[STR_LEN];

			if (input_string("Input file name:\n", str, STR_LEN) == 0) {
				if (save_car_table_to_file(&table, str) == 0)
					printf("\n{ Successfully saved }\n");
				else
					printf("\n{ Unable to save! }\n");
			}
		} else if (choice == 3) // Add
		{
			if (input_car(&ms) == 0) {
				if (add_to_car_table(&table, &ms) == 0)
					printf("\n{ Added new record }\n");
				else
					printf("\n{ Unable to add new record! }\n");
			}
		} else if (choice == 4) // Remove
		{
			int num;

			if (input_positive_int("Input record number to remove:\n", &num) == 0) {
				if (remove_from_car_table(&table, num) == 0)
					printf("\n{ Removed record }\n");
				else
					printf("\n{ Unable to remove record }\n");
			}
		} else if (choice == 5) // Sort table
		{
			sort_car_table(&table);
			printf("\n{ Sorted table }\n");
		} else if (choice == 6) // Print
		{
			print_car_table(&table);
		} else if (choice == 7) // Create key table
		{
			if (create_key_table(&table, &key_table) == 0)
				printf("\n{ Created key table }\n");
			else
				printf("\n{ Unable to create key table }\n");
		} else if (choice == 8) // Sort key table
		{
			sort_key_table(&key_table);
			printf("\n{ Sorted key table }\n");
		} else if (choice == 9) // Print key table
		{
			print_key_table(&key_table);
		} else if (choice == 10) // Print table in key order
		{
			if (print_car_table_by_key(&table, &key_table) != 0)
				printf("\n{ Invalid key table }\n");
		} else if (choice == 11) // Search
		{
			search();
		} else if (choice == 12) // Measure sorting time
		{
			measure_sorting_time();
		} else if (choice == 0) // Exit
		{
			return -1;
		} else
			printf("\n{ Invalid input }\n");
	} else {
		char c;

		do {
			scanf("%c", &c);

			if (c == EXIT_CHAR)
				return -1;
		} while (c != '\n' && c != EOF);

		printf("\n{ Invalid input }\n");
	}

	return 0;
}

int main(void) {
	while (menu() == 0);

	return 0;
}
