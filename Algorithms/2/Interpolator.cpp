//
// Created by ed on 04.04.17.
//

#include "Interpolator.h"

size_t Interpolator::calcIndexOfInterpolationPoint(double x) {
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

std::pair<size_t, size_t> Interpolator::calcInterpolationPoints(size_t index, unsigned int degree) {
	unsigned int num_necessary = degree + 1;
	if (degree >= points.size() - 2) {
		return std::pair<size_t, size_t>(0, points.size() - 1);
	}

	int remainder = num_necessary % 2;
	size_t equalization1 = index - num_necessary / 2 + 1;
	size_t equalization2 = index + num_necessary / 2 + remainder; // if necessary in odd points number next point is
	// getting from the end
	if (equalization1 <= 0) {
		return std::pair<size_t, size_t>(0, degree);
	}
	if (equalization2 >= points.size()) {
		return std::pair<size_t, size_t>(points.size() - num_necessary, points.size() - 1);
	}

	return std::pair<size_t, size_t>(equalization1, equalization2);
}

double Interpolator::runNewtonArrDividedDivision(size_t index1, size_t index2, double x) {
	size_t polynomial_degree = index2 - index1;
	std::vector<double> dividers;    // for divided differences calculation
	std::vector<double> X;
	std::vector<double> differences; // divided differences

	for (size_t i = index1; i <= index2; ++i) {
		X.push_back(points[i].x);
		dividers.push_back(points[i].y);
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

double Interpolator::Calc(double x, unsigned int degree) {
	auto index = calcIndexOfInterpolationPoint(x);
	auto indexes = calcInterpolationPoints(index, degree);
	auto interpolated_value = runNewtonArrDividedDivision(indexes.first, indexes.second, x);

	return interpolated_value;
}
