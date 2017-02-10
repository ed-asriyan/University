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

	}
}

#endif //INTEGRAL_EQUATIONS_HPP
