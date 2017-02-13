//
// Created by ed on 10.02.17.
//

#ifndef INTEGRAL_EQUATIONS_HPP
#define INTEGRAL_EQUATIONS_HPP

#include <algorithm>
#include <functional>
#include <exception>

namespace Solver {
	namespace Equations {
		class SolveErrorException : public std::exception {};

		/**
		 * @brief Solve equation func(x) = 0 by secants method
		 * @param func Function
		 * @param a First secant's point
		 * @param b Second secant's point
		 * @param eps Accuracy
		 * @return Root
		 */
		template<class T>
		T CalcSecants(const std::function<T(T)>& func, T a, T b, T eps) {
			eps = std::abs(eps);
			auto a_val = func(a);
			auto b_val = func(b);

			while ((std::abs(a_val) > eps && std::abs(b_val) > eps)) {
				// if secant is parallel to the OX
				if (a_val == b_val) {
					throw SolveErrorException();
				}

				// a must be left of b
				if (std::abs(a_val) < std::abs(b_val)) {
					std::swap(a_val, b_val);
					std::swap(a, b);
				}

				// move points
				auto tmp = b;
				b -= (b - a) * b_val / (b_val - a_val);
				a = tmp;

				// calculate new values
				a_val = func(a);
				b_val = func(b);
			}

			// return the value which is the closest to a zero
			return std::abs(a_val) < std::abs(b_val) ? a : b;
		}

		/**
		 * @brief Solve equation func(x) = 0 by tangents method
		 * @param func Function
		 * @param a Initial point
		 * @param b Second point (b - a) = tangent accurace
		 * @param eps X accuracy
		 * @return Root
		 *
		 * Tangents method.
		 *
		 * https://en.wikipedia.org/wiki/Newton's_method
		 */
		template<class T>
		T CalcTangents(const std::function<T(T)>& func, T a, T b, T eps) {
			double dx = b - a;
			auto df = [&func, &eps, &dx](double x) {
				return (func(x + dx) - func(x)) / dx;
			};

			double x1 = a - func(a) / df(a);
			double x0 = a;
			while (std::abs(x0 - x1) > eps) {
				x0 = x1;
				x1 = x1 - func(x1) / df(x1);
			}

			return std::abs(func(x1)) < std::abs(func(x0)) ? x1 : x0;
		}
	}
}

#endif //INTEGRAL_EQUATIONS_HPP
