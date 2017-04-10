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

class InputValues {
	public:
		struct Range {
			double begin;
			double end;
			unsigned int partitions;
			unsigned int count;
			double step;
		};

		InputValues()
			: InputValues(std::cin, std::cout) {}

		InputValues(std::istream& in, std::ostream& out) {
			out << "Enter x range:" << std::endl;
			out << " left : ";
			in >> x_range.begin;
			out << " right: ";
			in >> x_range.end;
			out << " partitions: ";
			in >> x_range.partitions;
			x_range.count = x_range.partitions + 1;
			x_range.step = (x_range.end - x_range.begin) / x_range.partitions;

			out << "Enter y range:" << std::endl;
			out << " left : ";
			in >> y_range.begin;
			out << " right: ";
			in >> y_range.end;
			out << " partitions: ";
			in >> y_range.partitions;
			y_range.count = y_range.partitions + 1;
			y_range.step = (y_range.end - y_range.begin) / y_range.partitions;

			out << "Enter degree:" << std::endl;
			out << " x: ";
			in >> degree.x;
			out << " y: ";
			in >> degree.y;

			out << "Enter point:" << std::endl;
			out << " x: ";
			in >> point.x;
			out << " y: ";
			in >> point.y;

			out << std::endl;
		}

		InputValues(int argc, const char* argv[]) {
			// todo:
		}

		const std::function<double(double, double)>& get_func() const {
			return func;
		}

		const Range& get_x_range() const {
			return x_range;
		}

		const Range& get_y_range() const {
			return y_range;
		}

		const Point2d& get_point() const {
			return point;
		}

		const Point2d& get_degree() const {
			return degree;
		}

	private:
		std::function<double(double, double)> func = Functions::Store2::F3;
		Range x_range;
		Range y_range;
		Point2d point;
		Point2d degree;
};

void FillMatrix(double* const* matrix, const InputValues& input_values) {
	auto func = input_values.get_func();
	auto x_range = input_values.get_x_range();
	auto y_range = input_values.get_y_range();

	for (unsigned int i = 0; i < y_range.count; ++i) {
		double y = y_range.begin + i * y_range.step;
		auto section_y = Functions::Store2::SectionY(func, y);
		auto iterators_x = FuncIterator::Create(section_y, y_range.begin, y_range.end, y_range.partitions);
		for (unsigned int j = 0; j < x_range.count; ++j) {
			double x = x_range.begin + j * x_range.step;
			double x_res = section_y(x);
			matrix[i][j] = x_res;
		}
	}
}

void PrintMatrix(std::ostream& out, const double* const* matrix, const InputValues& input_values) {
	auto x_range = input_values.get_x_range();
	auto y_range = input_values.get_y_range();

	const unsigned int CELL_WIDTH = 11;
	const unsigned int CELL_PRECISION = 3;
	std::cout << "Matrix:" << std::endl;
	std::cout << ' ' << std::setw(CELL_WIDTH) << ' ';
	for (auto i = 0; i < x_range.count; ++i) {
		double x = x_range.begin + i * x_range.step;
		std::cout << std::setw(CELL_WIDTH) << std::setprecision(CELL_PRECISION) << x;
	}
	std::cout << std::endl;
	std::cout << ' ' << std::setw(CELL_WIDTH) << ' ';
	for (unsigned int i = 0; i < x_range.count; ++i) {
		for (unsigned int j = 0; j < CELL_WIDTH; ++j) {
			std::cout << '-';
		}
	}
	std::cout << std::endl;
	for (unsigned int i = 0; i < y_range.count; ++i) {
		double y = y_range.begin + i * y_range.step;
		std::cout << std::setw(CELL_WIDTH) << std::setprecision(CELL_PRECISION) << y << "|";
		auto row = matrix[i];
		for (unsigned int j = 0; j < x_range.count; ++j) {
			std::cout << std::setw(CELL_WIDTH) << std::setprecision(CELL_PRECISION) << row[j];
		}
		std::cout << std::endl;
	}
}

int main(int argc, const char* argv[]) {
	InputValues input_values;
	auto func = input_values.get_func();
	auto x_range = input_values.get_x_range();
	auto y_range = input_values.get_y_range();

	// creating matrix
	double** matrix = new double* [y_range.count];
	for (unsigned int i = 0; i < y_range.count; ++i) {
		matrix[i] = new double[x_range.count];
	}
	FillMatrix(matrix, input_values);

	PrintMatrix(std::cout, (const double**) matrix, input_values);

	// free matrix
	for (int i = y_range.count - 1; i >= 0; --i) {
		delete[] matrix[i];
	}
	delete[] matrix;

	return 0;
}
