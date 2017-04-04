//
// Created by ed on 04.04.17.
//

#include "Equations.hpp"

double Equations::CalcTangents(double func(double), double a, double b, double eps) {
	const auto length = std::abs(a - b);

	auto df = [&func, &eps](double x) {
		const double dx = 1e-3;
		return (func(x + dx) - func(x)) / dx;
	};

	auto x1 = a - func(a) / df(a);
	auto x0 = a;
	while (std::abs(x0 - x1) > x0 * eps + eps) {
		x0 = x1;
		x1 = x1 - func(x1) / df(x1);
	}

	return std::abs(func(x1)) < std::abs(func(x0)) ? x1 : x0;
}
