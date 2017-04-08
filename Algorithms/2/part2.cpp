//
// Created by ed on 04.04.17.
//

#include <cmath>
#include <functional>

#include "Equations.hpp"
#include "Utils.hpp"

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

		inline auto CreateTable(
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

	return 0;
}
