//
// Created by ed on 05.04.17.
//

#ifndef LAB2_INTERPOLATION_HPP
#define LAB2_INTERPOLATION_HPP

#include <cstddef>
#include <memory>

namespace Interpolation {
	template<class ITERATOR>
	auto CalcIterpolatedFunc(ITERATOR begin, ITERATOR end) {
		size_t count = static_cast<size_t>(std::distance(begin, end));
		auto after_begin = begin;

		double* dividers = new double[count];    // for divided differences calculation
		double* X = new double[count];
		double* differences = new double[count]; // divided differences

		int _i = 0;
		for (auto it = begin; it != end; ++it, ++_i) {
			X[_i] = it->x;
			dividers[_i] = it->y;
			differences[_i] = 0;
		}

		auto polynomial_degree = count - 1;
		differences[0] = dividers[0];
		for (size_t i = 1; i <= polynomial_degree; ++i) {
			for (size_t j = 0; j <= polynomial_degree - i; ++j) {
				dividers[j] = (dividers[j + 1] - dividers[j]) / (X[j + i] - X[j]);
			}
			differences[i] = dividers[0];
		}

		double polynomial_sum = differences[0];

		delete[] dividers;

		std::shared_ptr<double> x_ptr(X);
		std::shared_ptr<double> d_ptr(differences);

		return [x_ptr, polynomial_degree, polynomial_sum, d_ptr](double x) {
			const auto x_values = x_ptr.get();
			const auto diffs = d_ptr.get();
			double ratio = 1;
			auto sum = polynomial_sum;

			for (int i = 1; i <= polynomial_degree; ++i) {
				ratio *= (x - x_values[i - 1]);
				sum += ratio * diffs[i];
			}

			return sum;
		};
	}

	template<class ITERATOR>
	std::pair<ITERATOR, ITERATOR> FindSubTableBorders(ITERATOR begin, ITERATOR end, double x, unsigned int degree) {
		unsigned int half = (degree + 1) / 2;

		/* Example for x = 4, degree=6
		 * Sequence: 0 1 2 3 4 5 6 7 8 9
		 *             ^     ^     ^
		 *          left   middle  right
		 */

		ITERATOR left = begin;
		ITERATOR middle = begin;
		ITERATOR right = begin;

		// moving middle to the initial position
		for (unsigned int i = 0; i < half; ++i) {
			++middle;
		}

		// moving right to the initial position
		right = middle;
		for (unsigned int i = half; i <= degree; ++i) {
			++right;
		}

		// searching subsequence position (left, middle, right) by moving right by step
		while (x > middle->x && right != end) {
			++left;
			++middle;
			++right;
		}

		return std::pair<ITERATOR, ITERATOR>(left, right);
	}
}

#endif //LAB2_INTERPOLATION_HPP
