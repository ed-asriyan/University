//
// Created by ed on 16.11.16.
//

#include "DNA_matrix.h"

DNA_matrix* create_dna_matrix(int count, int sequence_size) {
	DNA_matrix* dna = (DNA_matrix*) malloc(sizeof(DNA_matrix));

	char** data = (char**) malloc(sizeof(char*) * count);
	for (int i = 0; i < count; ++i) {
		data[i] = (char*) malloc(sizeof(char) * (sequence_size + 1));
	}

	dna->sequences = data;
	dna->sequence_count = count;
	dna->sequence_symbol_count = sequence_size;

	return dna;
}

void free_dna_matrix(DNA_matrix* dna) {
	for (int i = 0; i < dna->sequence_count; ++i) {
		free(dna->sequences[i]);
	}
	free(dna->sequences);

	dna->sequences = NULL;
	dna->sequence_count = 0;
	dna->sequence_symbol_count = 0;

	free(dna);
}
