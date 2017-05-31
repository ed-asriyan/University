//
// Created by ed on 21.04.17.
//

#ifndef LAB2_POINT1D_H
#define LAB2_POINT1D_H

#include <ostream>

/**
 * Point in one-dimensional space.
 */
struct Point1d {
	/**
	 * Default constructor.
	 */
	Point1d() = default;

	/**
	 * Constructor.
	 * @param x x coordinate
	 */
	Point1d(double x);


	double x;

	friend std::ostream& operator<<(std::ostream& out, const Point1d& point);
};

std::ostream& operator<<(std::ostream& out, const Point1d& point);
#endif //LAB2_POINT1D_H
