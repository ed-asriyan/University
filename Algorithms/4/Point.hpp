//
// Created by ed on 14.05.17.
//

#ifndef LAB4_POINT_HPP
#define LAB4_POINT_HPP

#include <ostream>

/**
 * Represents two-dimension point.
 */
struct Point {
	double x;
	double y;

	Point() = default;
	Point(double x, double y);
};

#endif //LAB4_POINT_HPP
