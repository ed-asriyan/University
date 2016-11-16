#include <stdio.h>

#include "DNA_matrix.h"

int work_with_stream(FILE* input, FILE* output) {
	int result = -2;
	int test_count = 0;

	if ((fscanf(input, "%d", &test_count) != 1) || test_count < 0) {
		return -1;
	}

	for (int i = 0; i < test_count; ++i) {
		int amount = 0;
		int sequence_size = 0;

		if ((fscanf(input, "%d%d", &amount, &sequence_size) != 2) || amount < 0 || sequence_size < 0) {
			return -1;
		}

		DNA_matrix* dna = create_dna_matrix(amount, sequence_size);

		for (int i = 0; i < amount; ++i) {
			if (fscanf(input, "%s", dna->sequences[i]) != 1) {
				free_dna_matrix(dna);
				return -1;
			}
		}

		result = calc_hamming_distance(dna);
		fprintf(output, "%s\n%d\n", dna->most_common_symbols, result);
		free_dna_matrix(dna);
	}

	return result;
}

int main(int argc, char* argv[]) {
	FILE* input = stdin;
	if (argc == 2) {
		input = fopen(argv[1], "r");
		if (input == NULL) {
			fprintf(stderr, "Can not open file %s.\n", argv[1]);
			return -1;
		}
	}

	const int result = work_with_stream(input, stdout);
	if (result < 0) {
		fprintf(stderr, "Error occurred (code %d).\n", result);
	}

	if (argc == 2) {
		fclose(input);
	}

	return 0;
}