#ifndef __ED_ASRIYAN_TABLE_CELL_H__
#define __ED_ASRIYAN_TABLE_CELL_H__

#include <stdlib.h>
#include <string.h>

// type enum which table cell may contains
enum DataType
{
	Integer,
	Double,
	Character,
	String
};

// represents table cell with data
typedef struct
{
	enum DataType type;
	char* data;
} TableCell;

// returns pointer to a TableCell object
TableCell* create_table_cell(char* data);

// destroys TableCell by pointer to it
void free_table_cell(TableCell* table_cell);


// returns data type in the cell
enum DataType get_data_type(TableCell* table_cell);

// returns data in the cell
char* get_data(TableCell* table_cell);


#endif //__ED_ASRIYAN_TABLE_CELL_H__