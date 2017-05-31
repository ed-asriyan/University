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

	template<class ITERATOR>
	auto CalcSplineFunc(ITERATOR begin, ITERATOR end) {
		int i;
		ITERATOR it0;
		ITERATOR it1;
		ITERATOR it2;

		auto n = std::distance(begin, end);

		auto public_array = new double[5 * n + 8];
		auto private_array = new double[7 * n + 13];

		auto h = private_array; // [n + 1];
		auto A = h + (n + 1); // [n + 2];
		auto B = A + (n + 2); // [n + 2];
		auto D = B + (n + 2); // [n + 2];
		auto F = D + (n + 2); // [n + 2];
		auto alpha = F + (n + 2); // [n + 2];
		auto beta = alpha + (n + 2); // [n + 2];

		auto Ca = public_array; // [n + 2];
		auto Cb = Ca + (n + 2); // [n + 2];
		auto Cc = Cb + (n + 2); // [n + 2];
		auto Cd = Cc + (n + 2); // [n + 2];
		auto args = Cd + (n + 2); // [n];

		i = 1;
		it0 = begin + i;
		it1 = begin + i - 1;
		while (i < n) {
			h[i] = it0->x - it1->x;

			++i;
			++it0;
			++it1;
		}

		i = 1;
		it1 = begin + i - 1;
		while (i < n) {
			Ca[i] = it1->y;

			++i;
			++it1;
		}
		Cc[1] = Cc[n] = 0;
		alpha[2] = beta[2] = 0;

		i = 2;
		it0 = begin + i;
		it1 = begin + i - 1;
		it2 = begin + i - 2;
		while (i < n) {
			A[i] = h[i - 1];
			B[i] = -2 * (h[i - 1] + h[i]);
			D[i] = h[i];
			F[i] = -3 * ((it0->y - it1->y) / h[i] - (it1->y - it2->y) / h[i - 1]);

			++i;
			++it0;
			++it1;
			++it2;
		}

		for (i = 2; i < n; i++) {
			alpha[i + 1] = D[i] / (B[i] - A[i] * alpha[i]);
			beta[i + 1] = (A[i] * beta[i] + F[i]) / (B[i] - A[i] * alpha[i]);
		}

		for (i = static_cast<int>(n) - 1; i > 1; i--) {
			Cc[i] = alpha[i + 1] * Cc[i + 1] + beta[i + 1];
		}

		i = 1;
		it0 = begin + i;
		it1 = begin + i - 1;
		while (i < n) {
			Cb[i] = (it0->y - it1->y) / h[i] - h[i] / 3 * (2 * Cc[i] + Cc[i + 1]);
			Cd[i] = (Cc[i + 1] - Cc[i]) / (3 * h[i]);

			++i;
			++it0;
			++it1;
		}

		delete[] private_array;

		i = 0;
		for (auto it = begin; it != end; ++it, ++i) {
			args[i] = it->x;
		}

		std::shared_ptr<double> public_ptr(public_array);

		return [public_ptr, n, args, Ca, Cb, Cc, Cd](double x) -> double {
			if (args[0] <= args[n - 2] && x < args[0]) {
				return -1;
			}
			int pos = 0;
			for (int i_ = 1; i_ < n - 1; ++i_) {
				if ((args[i_ - 1] <= x && x < args[i_]) || (args[i_ - 1] >= x && x > args[i_])) {
					break;
				}
				++pos;
			}
			++pos;

			return Ca[pos] + Cb[pos] * (x - args[pos - 1]) + Cc[pos] * (x - args[pos - 1]) * (x - args[pos - 1])
				+ Cd[pos] * (x - args[pos - 1]) * (x - args[pos - 1]) * (x - args[pos - 1]);
		};
	}
}

#endif //LAB2_INTERPOLATION_HPP
