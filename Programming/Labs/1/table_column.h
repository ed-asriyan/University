#ifndef __ED_ASRIYAN_TABLE_COLUMN_H__
#define __ED_ASRIYAN_TABLE_COLUMN_H__

#include <stdlib.h>
#include <string.h>

#include "table_cell.h"

// representes table column in the table
typedef struct
{
	int left_width;
	int right_width;
	int width;

	int cells_count;
	TableCell** cells;

	int filled_cells_count;
} TableColumn;

// returns pointer to a TableColumn object
TableColumn* create_table_column(int cells_count);

// destroys TableColumn by pointer to it
void free_table_column(TableColumn* table_column);


// adds data to the column
// if free space is availavle returns 1
// in another way returns -1
int add_cell(TableColumn* table_column, char* data);


// returns cells count in the table column
int get_cells_count(TableColumn* table_column);

// return filled cells count in the table column
int get_filled_cells_count(TableColumn* table_column);

// returns table column width
int get_width(TableColumn* table_column);

// returns table column right width
int get_right_width(TableColumn* table_column);

// returns table column left width
int get_left_width(TableColumn* table_column);

// if index is out of range returns NULL
// in another ways returns pointer to table cell by index
TableCell* get_cell(TableColumn* table_column, int index);

#endif // __ED_ASRIYAN_TABLE_COLUMN_H__