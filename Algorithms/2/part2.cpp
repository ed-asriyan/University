//
// Created by ed on 04.04.17.
//

#include <cmath>
#include <functional>
#include <iostream>
#include <iomanip>

#include "Equations.hpp"

namespace Functions {
	namespace Utils {
		inline auto Reverse(const std::function<double(double, double)>& func) {
			return [&func](double x, double y) {
				return func(y, x);
			};
		}

		inline auto SectionX(const std::function<double(double, double)>& func, double x) {
			return [x, func](double y) {
				return func(x, y);
			};
		}

		inline auto SectionY(const std::function<double(double, double)>& func, double y) {
			return [y, func](double x) {
				return func(x, y);
			};
		}

		inline auto MixFunc(
			const std::function<double(double, double)>& func1,
			const std::function<double(double, double)>& func2
		) {
			return [&func1, &func2](double x) {
				const double EPS = 1e-3;
				auto f1 = Equations::CalcTangents(SectionX(func1, x), x, EPS);
				auto f2 = Equations::CalcTangents(SectionX(func2, x), x, EPS);

				return std::pair<double, double>(f1, f2);
			};
		}
	}

	inline double F1(double x, double y) {
		return std::exp(x * x * x - y) - x * x * x * x * x * x + 2 * (y + 1) * (x * x * x) - y * y - 2 * y - 2;
	}

	inline double F2(double x, double y) {
		return std::exp(2 * std::log(x) - y) + y * std::exp(-y) - std::exp(x * x) * std::log(x * x + y);
	}
}

int main(int arc, const char* argv[]) {
	const double START = 0.1;
	const double END = 2;
	const double EPS = 1e-5;

	size_t n;
	std::cout << "Enter number of partition: ";
	std::cin >> n;
	double step = (END - START) / n;
	size_t points_number = n + 1;

	double degree;
	std::cout << "Enter the polynomial degree: ";
	std::cin >> degree;

	auto table = Functions::Utils::MixFunc(Functions::F1, Functions::F2);
	Point2d* points = new Point2d[points_number];

	const int COL_WIDTH = 12;
	std::cout << std::setw(COL_WIDTH) << "x" << ' '
	          << std::setw(COL_WIDTH) << "F1(x)" << ' '
	          << std::setw(COL_WIDTH) << "F2(x)" << ' '
	          << std::setw(COL_WIDTH) << "F1(x)-F2(x)" << ' '
	          << std::endl;
	for (int i = 0; i < points_number; ++i) {
		const auto x = START + i * step;
		auto pair = table(x);
		auto diff = pair.first - pair.second;
		std::cout << std::setw(COL_WIDTH) << x << ' '
		          << std::setw(COL_WIDTH) << pair.first << ' '
		          << std::setw(COL_WIDTH) << pair.second << ' '
		          << std::setw(COL_WIDTH) << diff << ' '
		          << std::endl;

		points[i].x = pair.second;
		points[i].y = diff;
	}

	auto min_iterator = std::min_element(points, points + points_number, [](const Point2d& a, const Point2d& b) {
		return std::abs(a.x) < std::abs(b.x);
	});
	return 0;
}
