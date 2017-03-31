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

int Solver::GetIndexofInterpolationPoint(
	const std::vector<Point>& points,
	double x
) {
	int result = -1;
	for (int i = 0; i < points.size(); ++i) {
		if (x < points[i].x) {
			result = i - 1;
			break;
		}
	}

	if (result == -1 && x > points[points.size() - 1].x) {
		result = static_cast<int>(points.size() - 1);
	}
	return result;
}
