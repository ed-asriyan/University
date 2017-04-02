//
// Created by ed on 31.03.17.
//

#include "solver.hpp"

Solver::Point::Point(double x, double y)
	: x(x), y(y) {}

Solver::PointsTable Solver::GenerateTable(
	const std::function<double(double)>& func,
	double x_begin,
	double x_end,
	double x_step
) {
	int count = static_cast<int>((x_end - x_begin) / x_step) + 1;
	Solver::PointsTable result(static_cast<unsigned int>(count));
	for (int i = 0; i < count; ++i) {
		double x = x_begin + i * x_step;
		result[i].x = x;
		result[i].y = func(x);
	}
	return result;
}

size_t Solver::GetIndexOfInterpolationPoint(
	const Solver::PointsTable& points,
	double x
) {
	bool is_found = false;
	size_t result = 0;
	for (size_t i = 0; i < points.size() && !is_found; ++i) {
		if ((is_found = x < points[i].x)) {
			result = i - 1;
		}
	}

	if (!is_found && x > points[points.size() - 1].x) {
		result = points.size() - 1;
	}
	return result;
}

std::pair<size_t, size_t> Solver::GetInterpolationPoints(
	const Solver::PointsTable& table,
	size_t index,
	unsigned int degree
) {
	unsigned int num_necessary = degree + 1;
	if (degree >= table.size() - 2) {
		return std::pair<size_t, size_t>(0, table.size() - 1);
	}

	int remainder = num_necessary % 2;
	size_t equalization1 = index - num_necessary / 2 + 1;
	size_t equalization2 = index + num_necessary / 2 + remainder; // if necessary in odd points number next point is
	// getting from the end
	if (equalization1 <= 0) {
		return std::pair<size_t, size_t>(0, degree);
	}
	if (equalization2 >= table.size()) {
		return std::pair<size_t, size_t>(table.size() - num_necessary, table.size() - 1);
	}

	return std::pair<size_t, size_t>(equalization1, equalization2);
}

double Solver::NewtonArrDividedDivision(
	const Solver::PointsTable& table,
	size_t index1,
	size_t index2,
	double x
) {
	size_t polynomial_degree = index2 - index1;
	std::vector<double> dividers;    // for divided differences calculation
	std::vector<double> X;
	std::vector<double> differences; // divided differences

	for (size_t i = index1; i <= index2; ++i) {
		X.push_back(table[i].x);
		dividers.push_back(table[i].y);
		differences.push_back(0);
	}
	differences[0] = dividers[0];
	for (size_t j = 1; j <= polynomial_degree; ++j) {
		for (size_t i = 0; i <= polynomial_degree - j; ++i) {
			dividers[i] = (dividers[i + 1] - dividers[i]) / (X[i + j] - X[i]);
			differences[j] = dividers[0];
		}
	}

	double polynomial_sum = differences[0];
	double polynomial_ratio = 1;
	for (int i = 1; i <= polynomial_degree; ++i) {
		polynomial_ratio *= (x - X[i - 1]);
		polynomial_sum += polynomial_ratio * differences[i];
	}

	return polynomial_sum;
}
