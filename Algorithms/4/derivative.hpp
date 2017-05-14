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
		INPUT_ITER it1 = begin;
		INPUT_ITER it0 = begin;
		++it0;
		while (it0 != end) {
			*(result_begin++) = Point(it1->x, (it0->y - it1->y) / (it0->x - it1->x));

			++it1;
			++it0;
		}
		*result_begin = Point((--end)->x, INFINITY);
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
		INPUT_ITER it2 = begin;
		INPUT_ITER it1;
		INPUT_ITER it0 = begin;
		++it0;
		it1 = it0;
		++it0;
		*result_begin = Point(begin->x, INFINITY);
		while (it0 != end) {
			*(result_begin++) = Point(it1->x, (it0->y - it2->y) / (it0->x - it2->x));

			++it2;
			++it1;
			++it0;
		}
		*result_begin = Point((--end)->x, INFINITY);
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
		auto n = std::distance(begin, end);

		auto b2 = begin;
		auto b0 = b2++;
		auto b1 = b2++;

		auto e3 = --end;
		auto e1 = e3--;
		auto e2 = e3--;

		auto dx0 = b2->x - b0->x;
		auto dxn = e1->x - e3->x;

		if (dx0) {
			*result_begin++ = Point(0, (-3 * b0->y + 4 * b1->y - b2->y) / dx0);
		} else {
			*result_begin++ = Point(0, INFINITY);
		}
		for (size_t i = 2; i < n; ++i) {
			*result_begin++ = Point(0, INFINITY);
		}
		if (dxn) {
			*result_begin++ = Point(0, (3 * e1->y - 4 * e2->y + e3->y) / dxn);
		} else {
			*result_begin++ = Point(0, INFINITY);
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
		auto n = std::distance(begin, end);
		Point* table = new Point[n];
		Point* table_i = table;
		for (auto it = begin; it != end; ++it) {
			*(table_i++) = Point(ksi(it->x), eta(it->y));
		}
		OneWayDifference(table, table + n, table);
		auto begin_i = begin;
		for (auto it = table; it != table + n; ++it) {
			it->y *= begin_i++->y;
		}
		table[n - 1].y = INFINITY;

		std::copy(table, table + n, result_begin);
		delete[] table;
	};
}

#endif //LAB4_DERIVATIVE_HPP
