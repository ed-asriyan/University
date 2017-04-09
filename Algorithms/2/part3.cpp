//
// Created by ed on 09.04.17.
//

#include <iostream>
#include <memory>
#include <iomanip>

#include "Point2d.h"
#include "Interpolation.hpp"

#include "Functions.hpp"
#include "FuncIterator.hpp"

int main(int argc, const char* argv[]) {
	const auto F1 = Functions::Store2::F1;

	double x_begin;
	std::cout << "Enter left  x border: ";
	std::cin >> x_begin;

	double x_end;
	std::cout << "Enter right x border: ";
	std::cin >> x_end;

	unsigned x_n;
	std::cout << "Enter x partition count: ";
	std::cin >> x_n;
	unsigned int x_count = x_n + 1;
	double x_step = (x_end - x_begin) / x_count;

	double y_begin;
	std::cout << "Enter left  y border: ";
	std::cin >> y_begin;

	double y_end;
	std::cout << "Enter right y border: ";
	std::cin >> y_end;

	unsigned y_n;
	std::cout << "Enter y partition count: ";
	std::cin >> y_n;
	unsigned int y_count = y_n + 1;
	double y_step = (y_end - y_begin) / y_count;

	Point2d point;
	std::cout << "Enter x: ";
	std::cin >> point.x;
	std::cout << "Enter y: ";
	std::cin >> point.y;

	unsigned int x_degree;
	std::cout << "Enter x degree: ";
	std::cin >> x_degree;

	unsigned int y_degree;
	std::cout << "Enter y degree: ";
	std::cin >> y_degree;

	// creating & printing matrix
	const unsigned int CELL_WIDTH = 11;
	const unsigned int CELL_PRECISION = 3;
	std::cout << "Matrix:" << std::endl;
	std::cout << ' ' << std::setw(CELL_WIDTH) << ' ';
	for (unsigned int i = 0; i < x_count; ++i) {
		double x = x_begin + i * x_step;
		std::cout << std::setw(CELL_WIDTH) << std::setprecision(CELL_PRECISION) << x;
	}
	std::cout << std::endl;
	std::cout << ' ' << std::setw(CELL_WIDTH) << ' ';
	for (unsigned int i = 0; i < x_count; ++i) {
		for (unsigned int j = 0; j < CELL_WIDTH; ++j) {
			std::cout << '-';
		}
	}
	std::cout << std::endl;
	Point2d** matrix = new Point2d* [x_count];
	for (unsigned int i = 0; i < x_count; ++i) {
		double x = x_begin + i * x_step;
		std::cout << std::setw(CELL_WIDTH) << std::setprecision(CELL_PRECISION) << x << "|";

		auto section_x = Functions::Store2::SectionX(F1, x);
		auto iterators_x = FuncIterator::Create(section_x, x_begin, x_end, x_n);
		matrix[i] = new Point2d[y_count];
		for (unsigned int j = 0; j < y_count; ++j) {
			double y = y_begin + j * y_step;
			matrix[i][j].x = x;
			const auto y_res = section_x(y);
			matrix[i][j].y = y_res;
			std::cout << std::setw(CELL_WIDTH) << std::setprecision(CELL_PRECISION) << y_res;
		}
		std::cout << std::endl;
	}

	// free matrix
	for (unsigned int i = 0; i < x_count; ++i) {
		delete[] matrix[i];
	}
	delete[] matrix;

	return 0;
}
