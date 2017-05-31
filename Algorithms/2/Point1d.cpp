//
// Created by ed on 21.04.17.
//

#include "Point1d.h"

Point1d::Point1d(double x)
	: x(x) {

}

std::ostream& operator<<(std::ostream& out, const Point1d& point) {
	return out << '(' << point.x << ')';
}
