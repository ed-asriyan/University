#include <iostream>
#include <iomanip>

#include "math_functions.hpp"
#include "solver.hpp"

class InputValues {
	public:
		InputValues()
			: InputValues(std::cin, std::cout) {}

		InputValues(std::istream& in, std::ostream& out) {
			out << "Enter left  border: ";
			in >> x_begin;
			out << "Enter right border: ";
			in >> x_end;
			out << "Enter step: ";
			in >> x_step;
			out << "Enter x: ";
			in >> x;
			out << "Enter polynomial degree: ";
			in >> degree;
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

		double get_x_step() const {
			return x_step;
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
		double x_step;
		double x;
		unsigned int degree;
};

void PrintTable(std::ostream& out, const std::vector<Solver::Point>& table) {
	for (auto& point: table) {
		out << std::setw(5) << point.x << ": " << point.y << std::endl;
	}
}

int main() {
	InputValues input_values;

	auto table = Solver::GenerateTable(Functions::F1,
	                                   input_values.get_x_begin(),
	                                   input_values.get_x_end(),
	                                   input_values.get_x_step());
	std::cout << "PointsTable:" << std::endl;
	PrintTable(std::cout, table);

	auto index = Solver::GetIndexOfInterpolationPoint(table, input_values.get_x());
	auto indexes = Solver::GetInterpolationPoints(table, index, input_values.get_degree());
	auto res = Solver::NewtonArrDividedDivision(table, indexes.first, indexes.second, input_values.get_x());

	std::cout << res << std::endl;

	return 0;
}
