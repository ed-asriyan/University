#ifndef STATEMACHINE_STACK_H
#define STATEMACHINE_STACK_H

#include <stdio.h>
#include <stdlib.h>

#define MULTIPLIER_COEF 2
#define compare(a, b) a < b ? a : b

typedef struct {
	char* base;
	char* next_item;

	int stack_size;
	int base_size;
} Stack;

Stack* create_stack();
void free_stack(Stack*);

void push_stack(Stack*, char);
char pop_stack(Stack*);
void print_stack(Stack*);

char top(Stack*);
int size(Stack*);
int is_empty(Stack*);

#endif //STATEMACHINE_STACK_H
