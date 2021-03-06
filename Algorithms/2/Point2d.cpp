//
// Created by ed on 04.04.17.
//

#include "Point2d.h"

Point2d::Point2d(double x, double y)
	: Point1d(x), y(y) {

}

Point2d::Point2d(const std::pair<double, double>& pair)
	: Point2d(pair.first, pair.second) {

}

std::ostream& operator<<(std::ostream& out, const Point2d& point) {
	return out << '(' << point.x << ", " << point.y << ')';
}
