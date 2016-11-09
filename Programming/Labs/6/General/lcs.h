//
// Created by ed on 09.11.16.
//

#ifndef LCS_LCS_H
#define LCS_LCS_H

#include <stdlib.h>

typedef struct {
	int height;
	int width;

	int** matrix;
	char** symbols;
} LCS;

/**
 * @brief Creates new LCS instance.
 * @param height Height of the LCS matrix.
 * @param width Width of the LCS matrix.
 * @return A pointer to new LCS object.
 */
LCS* create_lcs(int width, int height);

/**
 * @brief Destroys and free the LCS instance.
 * @param lcs Pointer to LCS object to destroy and free.
 */
void free_lcs(LCS* lcs);

/**
 * @brief Heaight of LCS matrix.
 * @param lcs Pointer to LCS object.
 * @return Heaight of LCS matrix.
 */
int get_lcs_height(const LCS* lcs);

/**
 * @brief Width of LCS matrix.
 * @param lcs Pointer to LCS object.
 * @return Width of LCS matrix.
 */
int get_lcs_width(const LCS* lcs);

/**
 * @brief LCS matrix.
 * @param lcs Pointer to LCS object.
 * @return LCS matrix.
 */
const int** get_lcs_matrix(LCS* lcs);

/**
 * @brief LCS char matrix.
 * @param lcs Pointer to LCS object.
 * @return LCS char matrix.
 */
const char** get_lcs_symbols(LCS* lcs);

#endif //LCS_LCS_H
