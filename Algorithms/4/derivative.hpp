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
	void LevelingDifference(INPUT_ITER begin, INPUT_ITER end, OUT_ITER result_begin) {
	};
}

#endif //LAB4_DERIVATIVE_HPP
