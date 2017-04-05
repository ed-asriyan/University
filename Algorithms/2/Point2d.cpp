//
// Created by ed on 04.04.17.
//

#include "Point2d.h"

Point2d::Point2d(double x, double y)
	: x(x), y(y) {

}

std::ostream& operator<<(std::ostream& out, const Point2d& point) {
	return out << '(' << point.x << ", " << point.y << ')';
}
