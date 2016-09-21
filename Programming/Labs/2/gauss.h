#ifndef __ED_ASRIYAN_GAUSS_H__
#define __ED_ASRIYAN_GAUSS_H__

#include <stdio.h>

#include "matrix.h"

// solves a equation system by Gauss method
// if solution completed returns 0
// if the system has not any solution result size is 0
int solve_gauss(Matrix* a, Matrix* result);

#endif // __ED_ASRIYAN_GAUSS_H__