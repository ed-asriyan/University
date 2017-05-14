#include <iostream>
#include <iomanip>
#include <iterator>
#include <functional>
#include <cmath>

#include "Point.hpp"

#include "derivative.hpp"

#define CELL_WIDTH 15

double f(double x) {
	return std::exp(x);
}

template<class ITERATOR>
void GenerateTable(
	const std::function<double(double)>& func,
	double left,
	double right,
	size_t points_number,
	ITERATOR result_first
) {
	auto step = (right - left) / (points_number == 1 ? points_number : points_number - 1);
	for (size_t i = 0; i < points_number; ++i) {
		double x = left + i * step;
		*(result_first++) = Point(x, func(x));
	}
}

std::ostream& operator<<(std::ostream& out, const Point& point) {
	return out << std::setw(CELL_WIDTH) << point.y;
}

template<class T>
std::ostream_iterator<T> get_stdout_iterator() {
	return std::ostream_iterator<T>(std::cout);
}

int main() {
	std::setprecision(CELL_WIDTH);

	double x_left;
	std::cout << "Enter left border:  ";
	std::cin >> x_left;

	double x_right;
	std::cout << "Enter right border: ";
	std::cin >> x_right;

	size_t x_count;
	std::cout << "Enter points number: ";
	std::cin >> x_count;

	Point* table = new Point[x_count];
	GenerateTable(f, x_left, x_right, x_count, table);

	std::cout << "   X    : ";
	for (const Point* it = table; it != table + x_count; ++it) {
		std::cout << std::setw(CELL_WIDTH) << it->x;
	}
	std::cout << std::endl;

	std::cout << " Source : ";
	std::copy(table, table + x_count, get_stdout_iterator<Point>());
	std::cout << std::endl;

	std::cout << "One-way : ";
	Derivative::OneWayDifference(table, table + x_count, get_stdout_iterator<Point>());
	std::cout << std::endl;

	std::cout << "Central : ";
	Derivative::CentralDifference(table, table + x_count, get_stdout_iterator<Point>());
	std::cout << std::endl;

	std::cout << " Border : ";
	Derivative::BorderDifference(table, table + x_count, get_stdout_iterator<Point>());
	std::cout << std::endl;

	std::cout << " Runge  : ";
	Derivative::RungeDifference(table, table + x_count, get_stdout_iterator<Point>());
	std::cout << std::endl;

	std::cout << "Leveling: ";
	Derivative::RungeDifference(table, table + x_count, get_stdout_iterator<Point>());
	std::cout << std::endl;

	return 0;
}
