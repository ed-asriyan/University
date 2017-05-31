//
// Created by ed on 26.04.17.
//

#include <algorithm>
#include <iostream>
#include <iomanip>

#include "Point2d.h"
#include "FuncIterator.hpp"
#include "Interpolation.hpp"

#include "Functions.hpp"

int main(int argc, const char* argv[]) {
	const auto func = Functions::Store1::F3;

	double x_begin;
	std::cout << "Enter left border:  ";
	std::cin >> x_begin;

	double x_end;
	std::cout << "Enter right border: ";
	std::cin >> x_end;

	size_t x_partitions;
	std::cout << "Enter partitions number: ";
	std::cin >> x_partitions;

	const auto iterators = FuncIterator::Create(func, x_begin, x_end, static_cast<int>(x_partitions));
	const auto x_count = std::distance(iterators.first, iterators.second);
	Point2d* table = new Point2d[x_count];
	std::copy(iterators.first, iterators.second, table);

	std::cout << std::endl;
	const std::streamsize default_precision = std::cout.precision();
	std::setprecision(4);
	for (size_t i = 0; i < x_count; ++i) {
		std::cout << std::setw(5) << table[i].x << " : " << std::setw(10) << table[i].y
		          << std::endl;
	}
	std::cout << std::endl;
	std::setprecision(static_cast<int>(default_precision));

	const auto interpolated_func = Interpolation::CalcSplineFunc(table, table + x_count);

	double x;
	std::cout << "Enter x:  ";
	std::cin >> x;

	const auto interpolated_result = interpolated_func(x);
	const auto real_result = func(x);

	std::cout << std::endl;
	std::cout << "Interpolated value: " << interpolated_result << std::endl;
	std::cout << "Real value        : " << real_result << std::endl;
	std::cout << "Difference        : " << std::abs(real_result - interpolated_result) << std::endl;

	delete[] table;

	return 0;
}
