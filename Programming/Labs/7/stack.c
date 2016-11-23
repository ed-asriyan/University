#include "stack.h"

Stack* create_stack() {
	Stack* stack = (Stack*) malloc(sizeof(Stack));

	stack->base = NULL;
	stack->next_item = NULL;
	stack->stack_size = 0;
	stack->base_size = 0;

	return stack;
}

void free_stack(Stack* stack) {
	free(stack->base);

	stack->base = NULL;
	stack->next_item = NULL;
	stack->stack_size = 0;
	stack->base_size = 0;

	free(stack);
}

void copy(const char* from, char* to, int count) {
	const char* f_ptr = from;
	char* t_ptr = to;

	for (int i = 0; i < count; ++i) {
		*(t_ptr + i) = *(f_ptr + i);
	}
}

void resize(Stack* stack, int new_size) {
	char* new_base = (char*) malloc(sizeof(char) * new_size);
	int size_to_copy = compare(stack->stack_size, new_size);

	if (stack->base && new_base) {
		copy(stack->base, new_base, size_to_copy);
	}

	free(stack->base);

	stack->base = new_base;
	stack->base_size = new_size;
}

void reserve(Stack* stack, int size) {
	int diff = stack->base_size - size;

	if (diff <= 0) {
		resize(stack, size * MULTIPLIER_COEF);
		stack->next_item = stack->base + size;
	} else {
		stack->next_item += size - stack->stack_size;
	}

	stack->stack_size = size;
}

void push_stack(Stack* stack, char value) {
	reserve(stack, stack->stack_size + 1);
	*(stack->next_item - 1) = value;
}

char pop_stack(Stack* stack) {
	if (is_empty(stack)) {
		return -1;
	}

	char result = *(stack->next_item - 1);
	reserve(stack, stack->stack_size - 1);

	return result;
}

void print_stack(Stack* stack) {
	for (int i = 0; i < stack->stack_size; ++i) {
		fprintf(stdout, "%c", stack->base[i]);
	}
	fprintf(stdout, "\n");
}

char top(Stack* stack) {
	return *(stack->next_item - 1);
}

int size(Stack* stack) {
	return stack->stack_size;
}

int is_empty(Stack* stack) {
	return stack->stack_size == 0;
}