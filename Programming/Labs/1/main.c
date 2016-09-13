#include <stdio.h>

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

	// todo

	fclose(input_stream); 
 
	return 0; 
}