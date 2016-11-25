//
// Created by ed on 28.11.16.
//

#include "StackInt.h"

// Stack part
// Constructors & destructors in C manner
IntStack* constructor() {
	IntStack* stack = (IntStack*) malloc(sizeof(IntStack));

	stack->base = NULL;
	stack->next_item = NULL;
	stack->stack_size = 0;
	stack->base_size = 0;

	return stack;
}

void destructor(IntStack* stack) {
	free(stack->base);

	stack->base = NULL;
	stack->next_item = NULL;
	stack->stack_size = 0;
	stack->base_size = 0;

	free(stack);
}

// ------------------------------------------------------------------------
// Stack build methods, usually declared private
void copy(const int* from, int* to, int count) {
	const int* f_ptr = from;
	int* t_ptr = to;

	for (int i = 0; i < count; ++i) {
		*(t_ptr + i) = *(f_ptr + i);
	}
}

void resize(IntStack* stack, int new_size) {
	int* new_base = (int*) malloc(sizeof(int) * new_size);
	int size_to_copy = compare(stack->stack_size, new_size);

	if (stack->base && new_base) {
		copy(stack->base, new_base, size_to_copy);
	}

	free(stack->base);

	stack->base = new_base;
	stack->base_size = new_size;
}

void reserve(IntStack* stack, int size) {
	int diff = stack->base_size - size;

	if (diff <= 0) {
		resize(stack, size * MULTIPLIER_COEF);
		stack->next_item = stack->base + size;
	} else {
		stack->next_item += size - stack->stack_size;
	}

	stack->stack_size = size;
}

// Stack public methods
void push(IntStack* stack, int value) {
	reserve(stack, stack->stack_size + 1);
	*(stack->next_item - 1) = value;
}

int pop(IntStack* stack) {
	if (empty(stack)) {
		return -1;
	}

	int result = *(stack->next_item - 1);
	reserve(stack, stack->stack_size - 1);

	return result;
}

void printStack(IntStack* stack) {
	for (int i = 0; i < stack->stack_size; ++i) {
		fprintf(stdout, "%d", stack->base[i]);
	}
	fprintf(stdout, "\n");
}

int top(IntStack* stack) {
	return *(stack->next_item - 1);
}

int size(IntStack* stack) {
	return stack->stack_size;
}

bool empty(IntStack* stack) {
	return stack->stack_size == 0;
}