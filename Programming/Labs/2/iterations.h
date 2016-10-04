//
// Created by ed on 10/5/16.
//

#ifndef EQUATIONSYSTEMSOLVER_ITERATIONS_H
#define EQUATIONSYSTEMSOLVER_ITERATIONS_H

#include <stdio.h>
#include <math.h>

#include "Matrix/matrix.h"

int solve_iterations(Matrix* a, Matrix* result, int iter_count, double epsilon);

#endif //EQUATIONSYSTEMSOLVER_ITERATIONS_H
