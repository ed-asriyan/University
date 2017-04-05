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
		++after_begin;

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
		for (size_t j = 1; j <= polynomial_degree; ++j) {
			for (size_t i = 0; i <= polynomial_degree - j; ++i) {
				dividers[i] = (dividers[i + 1] - dividers[i]) / (X[i + j] - X[i]);
				differences[j] = dividers[0];
			}
		}

		double polynomial_sum = differences[0];
		double polynomial_ratio = 1;

		return [X, polynomial_degree, polynomial_ratio, polynomial_sum, differences](double x) {
			for (int i = 1; i <= polynomial_degree; ++i) {
				polynomial_ratio *= (x - X[i - 1]);
				polynomial_sum += polynomial_ratio * differences[i];
			}
		};
	}
}

#endif //LAB2_INTERPOLATION_HPP
