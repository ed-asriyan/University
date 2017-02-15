#include <iostream>
#include <cmath>

#include "Integral.hpp"
#include "Equations.hpp"

/**
 * @brief Source math function
 * @tparam T Math function type
 * @param x First math argument
 * @param y Second math argument
 * @return Math function result
 */
template<class T = double>
T F(T x, T y) {
	return std::exp(x * x * x - y) - (x * x * x - y) * (x * x * x - y) + 2 * (x * x * x - y) - 2;
}

/**
 * @brief Calculates integral of implicitly given math function
 * @tparam T Math function type
 * @param func Math function
 * @param integral_func Function for calculating simple math function integral (like y(x))
 * @param equation_func Function for calculating simple math function root (like y(x) = 0)
 * @param left Left integral border (by X)
 * @param right Right integral border (by X)
 * @param eps Accuracy
 * @return Integral from left to right
 */
template<class T>
T CalcIntegral(
	const std::function<T(T, T)>& func,
	const std::function<T(const std::function<T(T)>&, T, T, T)>& integral_func,
	const std::function<T(const std::function<T(T)>&, T, T, T)>& equation_func,
	T left,
	T right,
	T eps
) {
	auto y = [&func, &equation_func, left, right, eps](T x) {
		auto section = [&func, &equation_func, x, left, right, eps](T yy) {
			return func(x, yy);
		};
		return equation_func(section, left, left + eps, eps);
	};

	return integral_func(y, left, right, eps);
}

int main() {
	typedef double arithmetic_t;

	std::cout << CalcIntegral<arithmetic_t>(
		F<arithmetic_t>,
		Solver::Integral::CalcSimpson<arithmetic_t>,
		Solver::Equations::CalcTangents<arithmetic_t>,
		0,
		2,
		1e-6
	) << std::endl;

	return 0;
}