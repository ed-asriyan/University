//
// Created by ed on 14.05.17.
//

#ifndef LAB4_DERIVATIVE_HPP
#define LAB4_DERIVATIVE_HPP

#include <algorithm>

#include "Point.hpp"

namespace Derivative {
	/**
	 * One-way difference.
	 * @tparam INPUT_ITER Input iterator.
	 * @tparam OUT_ITER Output iterator.
	 * @param begin Iterator to initial position in the table sequence.
	 * @param end Iterator to final position in the table sequence.
	 * @param result_begin Output iterator to the initial position in the destination sequence.
	 */
	template<class INPUT_ITER, class OUT_ITER>
	void OneWayDifference(INPUT_ITER begin, INPUT_ITER end, OUT_ITER result_begin) {
		auto b1 = begin;
		auto b0 = b1++;

		while (b0 != end) {
			*result_begin++ = (b0->y - b1->y) / (b0->x - b1->x);

			++b1;
			++b0;
		}
		*result_begin = NAN;
	};

	/**
	 * Central difference.
	 * @tparam INPUT_ITER Input iterator.
	 * @tparam OUT_ITER Output iterator.
	 * @param begin Iterator to initial position in the table sequence.
	 * @param end Iterator to final position in the table sequence.
	 * @param result_begin Output iterator to the initial position in the destination sequence.
	 */
	template<class INPUT_ITER, class OUT_ITER>
	void CentralDifference(INPUT_ITER begin, INPUT_ITER end, OUT_ITER result_begin) {
		auto b2 = begin;
		auto b0 = b2++;
		auto b1 = b2++;

		*result_begin++ = NAN;
		while (b2 != end) {
			*result_begin++ = (b2->y - b0->y) / (b2->x - b0->x);

			++b2;
			++b1;
			++b0;
		}
		*result_begin = NAN;
	};

	/**
	 * Border difference.
	 * @tparam INPUT_ITER Input iterator.
	 * @tparam OUT_ITER Output iterator.
	 * @param begin Iterator to initial position in the table sequence.
	 * @param end Iterator to final position in the table sequence.
	 * @param result_begin Output iterator to the initial position in the destination sequence.
	 */
	template<class INPUT_ITER, class OUT_ITER>
	void BorderDifference(INPUT_ITER begin, INPUT_ITER end, OUT_ITER result_begin) {
		const auto n = std::distance(begin, end);

		auto b2 = begin;
		auto b0 = b2++;
		auto b1 = b2++;

		auto e3 = --end;
		auto e1 = e3--;
		auto e2 = e3--;

		auto dx0 = b2->x - b0->x;
		auto dxn = e1->x - e3->x;

		if (dx0) {
			*result_begin++ = (-3 * b0->y + 4 * b1->y - b2->y) / dx0;
		} else {
			*result_begin++ = NAN;
		}
		for (size_t i = 2; i < n; ++i) {
			*result_begin++ = NAN;
		}
		if (dxn) {
			*result_begin = (3 * e1->y - 4 * e2->y + e3->y) / dxn;
		} else {
			*result_begin = NAN;
		}
	};

	/**
	 * Runge difference.
	 * @tparam INPUT_ITER Input iterator.
	 * @tparam OUT_ITER Output iterator.
	 * @param begin Iterator to initial position in the table sequence.
	 * @param end Iterator to final position in the table sequence.
	 * @param result_begin Output iterator to the initial position in the destination sequence.
	 */
	template<class INPUT_ITER, class OUT_ITER>
	void RungeDifference(INPUT_ITER begin, INPUT_ITER end, OUT_ITER result_begin) {
		const auto n = std::distance(begin, end);

		auto it2 = begin;
		auto it0 = it2++;
		auto it1 = it2++;

		const auto h = it1->x - it0->x;
		const auto h2 = h * 2;
		const double p = 1.0;
		const auto d = std::pow(2, p) - 1;

		for (size_t i = 2; i < n; ++i) {
			auto ksih = (it1->y - it0->y) / h;
			auto ksi2h = (it2->y - it0->y) / h2;
			*result_begin++ = ksih + (ksih - ksi2h) / d;

			++it0;
			++it1;
			++it2;
		}

		auto e4 = --end;
		auto e1 = e4--;
		auto e2 = e4--;
		auto e3 = e4--;

		auto ksih = (e2->y - e3->y) / h;
		auto ksi2h = (e2->y - e4->y) / h2;
		*result_begin++ = ksih + (ksih - ksi2h) / d;

		ksih = (e1->y - e2->y) / h;
		ksi2h = (e1->y - e3->y) / h2;
		*result_begin++ = ksih + (ksih - ksi2h) / d;
	};

	/**
	 * Leveling difference.
	 * @tparam INPUT_ITER Input iterator.
	 * @tparam OUT_ITER Output iterator.
	 * @param begin Iterator to initial position in the table sequence.
	 * @param end Iterator to final position in the table sequence.
	 * @param result_begin Output iterator to the initial position in the destination sequence.
	 */
	template<class INPUT_ITER, class OUT_ITER>
	void LevelingDifference(INPUT_ITER begin, INPUT_ITER end, OUT_ITER result_begin,
	                        const std::function<double(double)>& ksi,
	                        const std::function<double(double)>& eta
	) {
		const auto n = std::distance(begin, end);

		Point* const table = new Point[n];
		Point* table_i = table;

		for (auto it = begin; it != end; ++it) {
			*table_i++ = Point(ksi(it->x), eta(it->y));
		}

		const auto result = new double[n];
		OneWayDifference(table, table + n, result);

		auto begin_i = begin;
		for (auto it = result; it != result + n; ++it) {
			*it *= begin_i++->y;
		}
		result[n - 1] = NAN;

		std::copy(result, result + n, result_begin);

		delete[] result;
		delete[] table;
	};
}

#endif //LAB4_DERIVATIVE_HPP
