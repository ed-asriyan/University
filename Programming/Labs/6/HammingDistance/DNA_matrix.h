//
// Created by ed on 16.11.16.
//

#ifndef HAMMINGDISTANCE_DNA_MATRIX_H
#define HAMMINGDISTANCE_DNA_MATRIX_H

#include <stdlib.h>
#include <stdio.h>

/**
 * @brief DNA matrix.
 */
typedef struct {
	char** sequences;

	int sequence_count;
	int sequence_symbol_count;
} DNA_matrix;

/**
 * @brief Creates new DNA_Matrix instance.
 * @param count Sequence count.
 * @param sequence_size Sequence size.
 * @return  A pointer to new DNA_Matrix object.
 */
DNA_matrix* create_dna_matrix(int count, int sequence_size);

/**
 * @brief Destroys and free the DNA_Matrix instance.
 * @param lcs Pointer to DNA_Matrix object to destroy and free.
 */
void free_dna_matrix(DNA_matrix* dna);

#endif //HAMMINGDISTANCE_DNA_MATRIX_H
