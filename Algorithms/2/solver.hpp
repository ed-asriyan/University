//
// Created by ed on 29.03.17.
//

#ifndef LAB2_SOLVER_HPP
#define LAB2_SOLVER_HPP

#include <vector>
#include <functional>

namespace Solver {
	struct Point {
		Point() = default;
		Point(double x, double y);

		double x, y;
	};

	typedef std::vector<Point> PointsTable;

	/**
	 * Returns table of x and func(x).
	 *
	 * @param func Math function.
	 * @param x_begin Left border.
	 * @param x_end Right border.
	 * @param x_step Table step.
	 * @return table of x and func(x).
	 */
	PointsTable GenerateTable(
		const std::function<double(double)>& func,
		double x_begin,
		double x_end,
		double x_step
	);

	/**
	 * Returns index after which the interpolation point should be.
	 *
	 * @param points Points table.
	 * @param x Interpolation point.
	 * @return index after which the interpolation point should be.
	 */
	size_t GetIndexOfInterpolationPoint(
		const PointsTable& points,
		double x
	);

	/**
	 * Returns elements index from the table for interpolation algorithm.
	 *
	 * @param table Points table.
	 * @param index Point index.
	 * @param degree Polynomial degree.
	 * @return elements index from the table for interpolation algorithm.
	 */
	std::pair<size_t, size_t> GetInterpolationPoints(
		const PointsTable& table,
		size_t index,
		unsigned int degree
	);

	/**
	 * Calculates value of Newton's polynomial.
	 *
	 * @param table Points table.
	 * @param index1 Left index of the table.
	 * @param index2 Right index of the table.
	 * @param x Interpolation point.
	 * @return value of Newton's polynomial.
	 */
	double NewtonArrDividedDivision(
		const PointsTable& table,
		size_t index1,
		size_t index2,
		double x
	);
}

#endif //LAB2_SOLVER_HPP
