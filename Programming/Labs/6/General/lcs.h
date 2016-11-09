//
// Created by ed on 09.11.16.
//

#ifndef LCS_LCS_H
#define LCS_LCS_H

#include <stdlib.h>
/**
 * @brief Represents direction in LCS matix.
 */
typedef enum {
	RIGHT,
	DOWN,
	RIGHTDOWN
} Direction;

typedef struct {
	int height;
	int width;

	int** matrix;
	Direction** directions;
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
 * @brief LCS directions matrix.
 * @param lcs Pointer to LCS object.
 * @return LCS directions matrix.
 */
const Direction** get_lcs_directions(LCS* lcs);

#endif //LCS_LCS_H
