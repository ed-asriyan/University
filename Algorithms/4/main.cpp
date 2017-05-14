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

	Point* source = new Point[x_count];
	GenerateTable(f, x_left, x_right, x_count, source);

	Point* one_way_difference = new Point[x_count];
	Derivative::OneWayDifference(source, source + x_count, one_way_difference);

	Point* central_difference = new Point[x_count];
	Derivative::CentralDifference(source, source + x_count, central_difference);

	Point* border_difference = new Point[x_count];
	Derivative::BorderDifference(source, source + x_count, border_difference);

	Point* runge_difference = new Point[x_count];
	Derivative::RungeDifference(source, source + x_count, runge_difference);

	Point* leveling_difference = new Point[x_count];
	Derivative::LevelingDifference(source, source + x_count, leveling_difference,
	                               [](double x) { return x; },
	                               [](double y) { return std::log(y); }
	);

	std::cout <<
	          std::setw(CELL_WIDTH) << "X |" <<
	          std::setw(CELL_WIDTH) << "Source" <<
	          std::setw(CELL_WIDTH) << "One-way" <<
	          std::setw(CELL_WIDTH) << "Central-way" <<
	          std::setw(CELL_WIDTH) << "Border" <<
	          std::setw(CELL_WIDTH) << "Runge" <<
	          std::setw(CELL_WIDTH) << "Leveling" <<
	          std::endl;

	for (size_t i = 0; i < x_count; ++i) {
		std::cout <<
		          std::setw(CELL_WIDTH - 2) << source[i].x << " |" <<
		          std::setw(CELL_WIDTH) << source[i].y <<
		          std::setw(CELL_WIDTH) << one_way_difference[i].y <<
		          std::setw(CELL_WIDTH) << central_difference[i].y <<
		          std::setw(CELL_WIDTH) << border_difference[i].y <<
		          std::setw(CELL_WIDTH) << runge_difference[i].y <<
		          std::setw(CELL_WIDTH) << leveling_difference[i].y <<
		          std::endl;
	}

	delete[] leveling_difference;
	delete[] runge_difference;
	delete[] border_difference;
	delete[] central_difference;
	delete[] one_way_difference;
	delete[] source;

	return 0;
}
