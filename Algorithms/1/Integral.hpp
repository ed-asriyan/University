//
// Created by ed on 10.02.17.
//

#ifndef INTEGRAL_INTEGRAL_HPP
#define INTEGRAL_INTEGRAL_HPP

#include <functional>
#include <algorithm>

namespace Solver {
	namespace Integral {
		/**
		 * @brief Calculates an integral by trapezium method
		 * @param func The integrand function
		 * @param left_border Left integral border
		 * @param right_border Right integral border
		 * @param interval Trapezium width
		 * @return Integral from left_border to right_border
		 */
		template<class T>
		T CalcTrapezium(
			const std::function<T(T)>& func,
			T left_border,
			T right_border,
			T interval
		) {
			T result = static_cast<T>(0);
			T a = left_border;
			T b = a + interval;

			T a_val = func(a);
			T b_val = func(b);
			while (b < right_border) {
				result += (a_val + b_val) * interval;

				a = b;
				b += interval;
				a_val = b_val;
				b_val = func(b);
			}
			if (b != right_border) {
				b = right_border;
				b_val = func(b);
			}
			result += (a_val + b_val) * (b - a);
			result /= 2;

			return result;
		}
	};
}

#endif //INTEGRAL_INTEGRAL_HPP
