//
// Created by lieroz on 30.11.16.
// Modified by ed 07.12.16.
//

#include "dequeue.h"

Dequeue* create_dequeue() {
	Dequeue* self = (Dequeue*) malloc(sizeof(Dequeue));

	self->base = NULL;
	self->next_item = NULL;
	self->self_size = 0;
	self->base_size = 0;

	return self;
}

void free_sequeue(Dequeue* self) {
	free(self->base);

	self->base = NULL;
	self->next_item = NULL;
	self->self_size = 0;
	self->base_size = 0;

	free(self);
}

void copy(const int* from, int* to, int count) {
	const int* f_ptr = from;
	int* t_ptr = to;

	for (int i = 0; i < count; ++i) {
		*(t_ptr + i) = *(f_ptr + i);
	}
}

void resize(Dequeue* self, int new_size) {
	int* new_base = (int*) malloc(sizeof(int) * new_size);
	int size_to_copy = compare(self->self_size, new_size);

	if (self->base && new_base) {
		copy(self->base, new_base, size_to_copy);
	}

	free(self->base);

	self->base = new_base;
	self->base_size = new_size;
}

void reserve(Dequeue* self, int size) {
	int diff = self->base_size - size;

	if (diff <= 0) {
		resize(self, size * MULTIPLIER_COEF);
		self->next_item = self->base + size;
	} else {
		self->next_item += size - self->self_size;
	}

	self->self_size = size;
}

void push_front(Dequeue* self, int value) {
	reserve(self, self->self_size + 1);

	for (int i = self->self_size - 1; i > 0; --i) {
		*(self->base + i) = *(self->base + i - 1);
	}

	*(self->base) = value;
}

int pop_front(Dequeue* self) {
	if (empty(self)) {
		return -1;
	}

	int result = *(self->base);

	for (int i = 0; i < self->self_size - 1; ++i) {
		*(self->base + i) = *(self->base + i + 1);
	}

	reserve(self, self->self_size - 1);

	return result;
}

void push_back(Dequeue* self, int value) {
	reserve(self, self->self_size + 1);
	*(self->next_item - 1) = value;
}

int pop_back(Dequeue* self) {
	if (empty(self)) {
		return -1;
	}

	int result = *(self->next_item - 1);
	reserve(self, self->self_size - 1);

	return result;
}

void to_sdtout(const Dequeue* self) {
	for (size_t i = 0; i < self->self_size; ++i) {
		fprintf(stdout, "%d ", self->base[i]);
	}

	fprintf(stdout, "\n");
}

int size(const Dequeue* self) {
	return self->self_size;
}

bool empty(const Dequeue* self) {
	return self->self_size == 0;
}