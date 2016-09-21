#ifndef __ED_ASRIYAN_TABLE_H__
#define __ED_ASRIYAN_TABLE_H__

#include <stdlib.h>
#include <stdio.h>

#include "table_cell.h"
#include "table_column.h"

// represents the table
typedef struct
{
	FILE* stream;

	int columns_count;
	int rows_count;

	TableColumn** columns;

	int filled;
} Table;

// returns pointer to a Table object
// if read failed returns NULL
Table* create_table(FILE* input_stream);

// destroys Table by pointer to it
void free_table(Table* table);

// prints the table to the stream in formatted view
void print_table(FILE* output_stream, Table* table);

#endif // __ED_ASRIYAN_TABLE_H__