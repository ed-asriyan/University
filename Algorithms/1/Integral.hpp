//
// Created by ed on 10.02.17.
//

#ifndef INTEGRAL_INTEGRAL_HPP
#define INTEGRAL_INTEGRAL_HPP

#include <functional>
#include <algorithm>
#include <type_traits>

namespace Solver {
	namespace Integral {
		/**
		 * @brief Calculates an integral by trapezium method
		 * @tparam T Arithmetic type
		 * @param func The integrand function
		 * @param left_border Left integral border
		 * @param right_border Right integral border
		 * @param n Interval count
		 * @return Integral from left_border to right_border
		 *
		 * Trapezium method.
		 * https://en.wikipedia.org/wiki/Trapezoidal_rule
		 */
		template<class T>
		T CalcTrapezium(
			const std::function<T(T)>& func,
			T left_border,
			T right_border,
			size_t n
		) {
			static_assert(std::is_arithmetic<T>::value, "T must be arithmetic type");

			const auto interval = (right_border - left_border) / n;

			T result = (func(left_border) + func(right_border)) / 2;

			for (size_t i = 1; i < n; ++i) {
				auto x = left_border + i * interval;
				result += func(x);
			}

			return result * interval;
		}
	}
}

#endif //INTEGRAL_INTEGRAL_HPP
