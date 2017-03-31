//
// Created by ed on 31.03.17.
//

#include "solver.hpp"

std::vector<Solver::Point> Solver::GenerateTable(
	const std::function<double(double)>& func,
	double x_begin,
	double x_end,
	double x_step
) {
	int count = static_cast<int>((x_end - x_begin) / x_step) + 1;
	std::vector<Solver::Point> result(static_cast<unsigned int>(count));
	for (int i = 0; i < count; ++i) {
		double x = x_begin + i * x_step;
		result[i] = {x, func(x)};
	}
	return result;
}
