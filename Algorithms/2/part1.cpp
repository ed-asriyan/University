#include <iostream>
#include <iomanip>
#include <cmath>

#include "Interpolation.hpp"
#include "FuncIterator.hpp"
#include "Functions.hpp"

class InputValues {
	public:
		InputValues()
			: InputValues(std::cin, std::cout) {}

		InputValues(std::istream& in, std::ostream& out) {
			out << "Enter left  border: ";
			in >> x_begin;
			out << "Enter right border: ";
			in >> x_end;
			out << "Enter n: ";
			in >> n;
			out << "Enter x: ";
			in >> x;
			out << "Enter polynomial degree: ";
			in >> degree;

			out << std::endl;
		}

		InputValues(int argc, const char* argv[]) {
			// todo:
		}

		double get_x_begin() const {
			return x_begin;
		}

		double get_x_end() const {
			return x_end;
		}

		int get_n() const {
			return n;
		}

		double get_x() const {
			return x;
		}

		unsigned int get_degree() const {
			return degree;
		}

	private:
		double x_begin;
		double x_end;
		int n;
		double x;
		unsigned int degree;
};

template<class ITERATOR>
void PrintTable(std::ostream& out, const ITERATOR& begin, const ITERATOR& end) {
	for (auto it = begin; it != end; ++it) {
		out << std::setw(5) << it->x << ": " << it->y << std::endl;
	}
}

void RunTest(const InputValues& input_values, const std::function<double(double)>& func, std::ostream& out) {
	const auto points_count = input_values.get_n() + 1;
	const auto left_x = input_values.get_x_begin();
	const auto right_x = input_values.get_x_end();
	const auto x = input_values.get_x();
	const auto degree = input_values.get_degree();

	const auto iterators = FuncIterator::Create(func,
	                                            left_x,
	                                            right_x,
	                                            points_count - 1);

	Point2d* table = new Point2d[std::distance(iterators.first, iterators.second)];
	std::copy(iterators.first, iterators.second, table);

	out << "Points table:" << std::endl;
	PrintTable(std::cout, table, table + points_count);
	out << std::endl;

	auto borders =
		Interpolation::FindSubTableBorders(
			table,
			table + points_count,
			x,
			degree
		);

	auto interpolated_fun = Interpolation::CalcIterpolatedFunc(borders.first, borders.second);
	auto interpolated_value = interpolated_fun(x);
	auto real_value = func(x);

	out << "Interpolated value: " << interpolated_value << std::endl;
	out << "Real value        : " << real_value << std::endl;
	out << "Difference        : " << std::abs(interpolated_value - real_value) << std::endl;

	delete[] table;
}

int main() {
	InputValues input_values;
	RunTest(input_values, Functions::Store1::F1, std::cout);

	return 0;
}
