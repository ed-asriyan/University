//
// Created by ed on 04.04.17.
//

#ifndef LAB2_POINT2D_H
#define LAB2_POINT2D_H

#include <ostream>

/**
 * Point in two-dimensional space.
 */
struct Point2d {
	/**
	 * Default constructor.
	 */
	Point2d() = default;

	/**
	 * Constructor.
	 * @param x x coordinate
	 * @param y y coordinate
	 */
	Point2d(double x, double y);

	/**
	 * Constructor.
	 * @param pair pair of x and y coordinate
	 */
	Point2d(const std::pair<double, double>& pair);

	double x, y;

	friend std::ostream& operator<<(std::ostream& out, const Point2d& point);
};

std::ostream& operator<<(std::ostream& out, const Point2d& point);

#endif //LAB2_POINT2D_H
