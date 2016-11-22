#include <stdio.h>

#include "state_machine.h"

int main(void) {
	printf("<Table_of_tokens>\n");
	read_from_stream(stdin, stdout);
	fprintf(stdout, "</Table_of_tokens>\n");

	return 0;
}