#include "table_column.h"
#include <stdio.h>
// if str contains c returns position of c
// in another way returns str length
int str_pos(char* str, char c)
{
	int i;
	for (i = 0; *str != '\0' && *str != c; ++i, ++str) ;
	return --i;
}

// returns pointer to a TableColumn object
TableColumn* create_table_column(int cells_count)
{
	TableColumn* result = (TableColumn*)malloc(sizeof(TableColumn));

	result->cells_count = cells_count;
	result->cells = (TableCell**)malloc(sizeof(TableCell*) * cells_count);
	result->width = 0;
	result->left_width = 0;
	result->right_width = 0;
	result->filled_cells_count = 0;

	return result;
}

// destroys TableColumn by pointer to it
void free_table_column(TableColumn* table_column)
{
	int cells_count = table_column->filled_cells_count;
	TableCell** cell = table_column->cells;
	for (int i = 0; i < cells_count; ++i, ++cell) {
		free_table_cell(*cell);
	}
	free(table_column->cells);

	free(table_column);
}

// adds data to the column
// if free space is availavle returns 1
// in another way returns -1
int add_cell_column(TableColumn* table_column, char* data)
{
	if (table_column->filled_cells_count >= table_column->cells_count) {
		return -1;
	}

	int data_length = strlen(data);

	if (get_data_type_cell(table_column->cells[table_column->filled_cells_count++] = create_table_cell(data)) == Double) {
		int left_width = str_pos(data, '.') + 1;
		int right_width = data_length - left_width;

		if (left_width > table_column->left_width) {
			table_column->left_width = left_width;
			data_length = table_column->right_width + left_width;
		}
		if (right_width > table_column->right_width) {
			table_column->right_width = right_width;
			data_length = table_column->left_width + right_width;
		}
	}
	if (!data_length) {
		data_length = 4;
	}
	if (data_length > table_column->width) {
		table_column->width = data_length;
	}

	return 1;
}

// returns cells count in the table column
int get_cells_count_column(TableColumn* table_column)
{
	return table_column->cells_count;
}

// return filled cells count in the table column
int get_filled_cells_count_column(TableColumn* table_column)
{
	return table_column->filled_cells_count;
}

// returns table column width
int get_width_column(TableColumn* table_column)
{
	return table_column->width;
}

// returns table column right width
int get_right_width_column(TableColumn* table_column)
{
	return table_column->right_width;
}

// returns table column left width
int get_left_width_column(TableColumn* table_column)
{
	return table_column->left_width;
}

// if index is out of range returns NULL
// in another ways returns pointer to table cell by index
TableCell* get_cell_column(TableColumn* table_column, int index)
{
	if (index < 0 || index >= table_column->filled_cells_count) {
		return NULL;
	}

	return table_column->cells[index];
}