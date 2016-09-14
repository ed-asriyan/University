#include <stdio.h>

#include "table.h"

int main(int argc, char* argv[]) 
{
	if (argc != 2) { 
		printf("Invalid args\n"); 
		return -1; 
	} 
 
	FILE* input_stream = fopen(argv[1], "r"); 
	if (input_stream == NULL) { 
		printf("Can not open file\n"); 
		return -2; 
	}

	Table* table = create_table(input_stream);

	if (table != NULL) {
		print_table(stdout, table);

		free_table(table);
	}

	fclose(input_stream); 
 
	return 0; 
}