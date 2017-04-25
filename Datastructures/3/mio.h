#ifndef MIO_H
#define MIO_H

#include <stdio.h>

#define EXIT_CHAR 5  // Ctrl + E

int input_positive_int(char* msg, int* ptr_i);

int input_binary(char* msg, int* ptr_i);

int input_string(char* msg, char* str, int max_len);

#endif
