#include <iostream>
#include <cmath>

#include "Integral.hpp"
#include "Equations.hpp"

template<class T = double>
T F(T x, T y) {
	return std::exp(x * x * x - y) - (x * x * x - y) * (x * x * x - y) + 2 * (x * x * x - y) - 2;
}

template<class T>
T CalcIntegral(
	const std::function<T(const std::function<T(T)>&, T, T, T)>& integral_func,
	const std::function<T(const std::function<T(T)>&, T, T, T)>& equation_func,
	double left,
	double right,
	double eps = 0.001
) {
	auto y = [&equation_func, left, right, eps](double x) {
		auto section = [equation_func, x, left, right, eps](double yy) {
			return F(x, yy);
		};
		return equation_func(section, left, left + eps, eps);
	};

	return integral_func(y, left, right, eps);
}

int main() {
	std::cout << CalcIntegral<double>(
		Solver::Integral::CalcTrapezium<double>,
		Solver::Equations::CalcSecants<double>,
		0,
		2
	) << std::endl;

	return 0;
}