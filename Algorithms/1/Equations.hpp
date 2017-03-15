//
// Created by ed on 10.02.17.
//

#ifndef INTEGRAL_EQUATIONS_HPP
#define INTEGRAL_EQUATIONS_HPP

#include <algorithm>
#include <functional>
#include <exception>
#include <type_traits>

namespace Solver {
	namespace Equations {
		class SolveErrorException : public std::exception {};

		/**
		 * @brief Solve equation func(x) = 0 by tangents method
		 * @tparam T Arithmetic type
		 * @param func Function
		 * @param a Initial point
		 * @param b Second point (b - a) = tangent accuracy
		 * @param eps X accuracy
		 * @return Root
		 *
		 * Tangents method.
		 * https://en.wikipedia.org/wiki/Newton's_method
		 */
		template<class T>
		T CalcTangents(const std::function<T(T)>& func, T a, T b, double eps) {
			static_assert(std::is_arithmetic<T>::value, "T must be arithmetic type");

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
	}
}

#endif //INTEGRAL_EQUATIONS_HPP
