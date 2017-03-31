#include <iostream>

#include "math_functions.hpp"
#include "solver.hpp"

int main() {
	auto table = Solver::GenerateTable(Functions::F1, 0, 2, 0.1);

	return 0;
}
