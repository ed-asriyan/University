#include "table_cell.h"

// returns 1 if c is digit
int is_digit(char c) {
	return c >= '0' && c <= '9';
}

// returns real data type
enum DataType recognize_data_type(char* data) {
	int length = 0;

	int digits_count = 0;
	int dot_count = 0;
	int symbols_count = 0;

	while (*data != '\0') {
		digits_count += is_digit(*data);
		dot_count += *data == '.';
		++length;

		++data;
	}
	symbols_count = length - digits_count - dot_count;

	if (!length) {
		return String;
	} else if (!symbols_count) {
		if (!dot_count) {
			return Integer;
		} else if (length != 1) {
			return Double;
		} else {
			return Character;
		}
	} else {
		if (length == 1) {
			return Character;
		} else {
			return String;
		}
	}

	// if this algorithm doesn't work as it should work
	return -100500;
}

// returns pointer to a TableCell object
TableCell* create_table_cell(char* data) {
	TableCell* result = (TableCell*)malloc(sizeof(TableCell));

	result->type = recognize_data_type(data);
	result->data = (char*)malloc(sizeof(char) * strlen(data));
	strcpy(result->data, data);

	return result;
}

// destroys TableCell by pointer to it
void free_table_cell(TableCell* table_cell) {
	free(table_cell->data);
	free(table_cell);
}

// returns data type in the cell
enum DataType get_data_type(TableCell* table_cell) {
	return table_cell->type;
}

// returns data in the cell
char* get_data(TableCell* table_cell) {
	return table_cell->data;
}