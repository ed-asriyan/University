#include "table_cell.h"

// returns 1 if c is digit
int is_digit(char c)
{
	return c >= '0' && c <= '9';
}

// returns real data type
enum DataType recognize_data_type(char* data)
{
	int length = 0;

	int digits_count = 0;
	int dot_count = 0;
	int minus_pos = -1;
	int minus_count = 0;
	int symbols_count = 0;

	while (*data != '\0') {
		digits_count += is_digit(*data);
		dot_count += *data == '.';
		if (*data == '-') {
			minus_pos = length;
			++minus_count;
		}
		++length;

		++data;
	}
	symbols_count = length - digits_count - dot_count - minus_count;

	if (minus_pos <= 0 && digits_count && 
	    digits_count + minus_count == length) {
		return Integer;
	} else if (minus_pos <= 0 && dot_count <= 1 && digits_count &&
	           digits_count + dot_count + minus_count == length) {
		return Double;
	} else if (!digits_count && length == 1) {
		return Character;
	} else {
		return String;
	}

	// if this algorithm doesn't work as it should work
	return -100500;
}

// returns pointer to a TableCell object
TableCell* create_table_cell(char* data)
{
	TableCell* result = (TableCell*)malloc(sizeof(TableCell));

	result->type = recognize_data_type(data);
	result->width = strlen(data);

	return result;
}

// destroys TableCell by pointer to it
void free_table_cell(TableCell* table_cell)
{
	free(table_cell);
}

// returns data type in the cell
enum DataType get_data_type_cell(TableCell* table_cell)
{
	return table_cell->type;
}

// returns cell width
int get_width_cell(TableCell* table_cell)
{
	return table_cell->width;
}