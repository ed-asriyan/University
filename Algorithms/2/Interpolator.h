//
// Created by ed on 04.04.17.
//

#ifndef LAB2_INTERPOLATOR_H
#define LAB2_INTERPOLATOR_H

#include <cstddef>
#include <vector>

#include "Point2d.h"

/**
 * Newton interpolator.
 */
class Interpolator {
	public:
		/**
		 * Range constructor.
		 *
		 * @param begin Iterator to the initial position of the points.
		 * @param end Iterator to the final position of the points.
		 */
		template<class ITERATOR>
		Interpolator(ITERATOR begin, ITERATOR end);

		/**
		 * Calculates Newton-interpolated function value.
		 * @param x Interpolation point.
		 * @param degree Interpolation degree.
		 * @return Newton-interpolated function value.
		 */
		double Calc(double x, unsigned int degree);

	private:
		size_t calcIndexOfInterpolationPoint(double x);
		std::pair<size_t, size_t> calcInterpolationPoints(size_t index, unsigned int degree);
		double runNewtonArrDividedDivision(size_t index1, size_t index2, double x);

		const std::vector<Point2d> points;

};

template<class ITERATOR>
Interpolator::Interpolator(ITERATOR begin, ITERATOR end)
	: points(begin, end) {

}

#endif //LAB2_INTERPOLATOR_H
