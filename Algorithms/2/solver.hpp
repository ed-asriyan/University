//
// Created by ed on 29.03.17.
//

#ifndef LAB2_SOLVER_HPP
#define LAB2_SOLVER_HPP

#include <algorithm>
#include <functional>

#include "point.hpp"

namespace Solver {
	struct Point {
		double x, y;
	};

	/**
	 * Returns table of x and func(x).
	 *
	 * @param func Math function.
	 * @param x_begin Left border.
	 * @param x_end Right border.
	 * @param x_step Table step.
	 * @return Table of x and func(x).
	 */
	std::vector<Point> GenerateTable(
		const std::function<double(double)>& func,
		double x_begin,
		double x_end,
		double x_step
	);
}

#endif //LAB2_SOLVER_HPP
