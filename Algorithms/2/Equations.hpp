//
// Created by ed on 04.04.17.
//

#ifndef LAB2_EQUATIONS_HPP
#define LAB2_EQUATIONS_HPP

#include <algorithm>
#include <exception>
#include <functional>

namespace Equations {
	class SolveErrorException : public std::exception {};

	/**
	 * @brief Solve equation func(x) = 0 by tangents method
	 * @param func Function
	 * @param a Initial point
	 * @param b Second point (b - a) = tangent accuracy
	 * @param eps X accuracy
	 * @return Root
	 *
	 * Tangents method.
	 * https://en.wikipedia.org/wiki/Newton's_method
	 */
	double CalcTangents(const std::function<double(double)>& func, double a, double eps);
}

#endif //LAB2_EQUATIONS_HPP
