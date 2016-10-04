//
// Created by ed on 10/5/16.
//

#ifndef EQUATIONSYSTEMSOLVER_GAUSS_H
#define EQUATIONSYSTEMSOLVER_GAUSS_H

#include <stdio.h>

#include "Matrix/matrix.h"

// solves a equation system by Gauss method
// if solution completed returns 0
// if the system has not any solution result size is 0
int solve_gauss(Matrix* a, Matrix* result);

#endif //EQUATIONSYSTEMSOLVER_GAUSS_H
