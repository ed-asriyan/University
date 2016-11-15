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

char* seek_common_elements(DNA_matrix* dna) {
	char* most_common_symbols = (char*) malloc(sizeof(char) * (dna->sequence_symbol_count + 1));

	for (int i = 0; i < dna->sequence_symbol_count; ++i) {
		int most_common_symbol_count = 0;
		char smallest_character = 'Z';

		for (int j = 0; j < dna->sequence_count; ++j) {
			int count = 1;

			for (int k = j + 1; k < dna->sequence_count; ++k) {

				if (dna->sequences[j][i] == dna->sequences[k][i]) {
					++count;
				}
			}

			if (count > most_common_symbol_count) {
				most_common_symbol_count = count;
				most_common_symbols[i] = dna->sequences[j][i];
			}

			if (count == most_common_symbol_count && dna->sequences[j][i] < smallest_character) {
				smallest_character = dna->sequences[j][i];
				most_common_symbols[i] = dna->sequences[j][i];
			}
		}
	}

	most_common_symbols[dna->sequence_symbol_count] = '\0';

	return most_common_symbols;
}

int calc_hamming_distance(DNA_matrix* dna) {
	char* most_common_symbols = seek_common_elements(dna);
	int hamming_distance = 0;

	for (int i = 0; i < dna->sequence_symbol_count; ++i) {
		for (int j = 0; j < dna->sequence_count; ++j) {

			if (dna->sequences[j][i] != most_common_symbols[i]) {
				++hamming_distance;
			}
		}
	}

	free(most_common_symbols);
	return hamming_distance;
}