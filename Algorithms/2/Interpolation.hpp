//
// Created by ed on 05.04.17.
//

#ifndef LAB2_INTERPOLATION_HPP
#define LAB2_INTERPOLATION_HPP

#include <cstddef>
#include <vector>

namespace Interpolation {
	template<class ITERATOR>
	auto CalcIterpolatedFunc(ITERATOR begin, ITERATOR end) {
		auto after_begin = begin;

		std::vector<double> dividers;    // for divided differences calculation
		std::vector<double> X;
		std::vector<double> differences; // divided differences

		for (auto it = begin; it != end; ++it) {
			X.push_back(it->x);
			dividers.push_back(it->y);
			differences.push_back(0);
		}

		auto polynomial_degree = X.size() - 1;
		differences[0] = dividers[0];
		for (size_t i = 1; i <= polynomial_degree; ++i) {
			for (size_t j = 0; j <= polynomial_degree - i; ++j) {
				dividers[j] = (dividers[j + 1] - dividers[j]) / (X[j + i] - X[j]);
				differences[i] = dividers[0];
			}
		}

		double polynomial_sum = differences[0];
		double polynomial_ratio = 1;

		return [X, polynomial_degree, polynomial_ratio, polynomial_sum, differences](double x) {
			auto ratio = polynomial_ratio;
			auto sum = polynomial_sum;

			for (int i = 1; i <= polynomial_degree; ++i) {
				ratio *= (x - X[i - 1]);
				sum += ratio * differences[i];
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
		 *          left   meddle  right
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
