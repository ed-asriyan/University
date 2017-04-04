//
// Created by ed on 04.04.17.
//

#include <cmath>

namespace Functions {
	inline double reverse(double func(double, double), double x, double y) {
		return func(y, x);
	}

	double F1(double x, double y) {
		return std::exp(x * x * x - y) - x * x * x * x * x * x + 2 * (y + 1) * (x * x * x) - y * y - 2 * y - 2;
	}

	double F2(double x, double y) {
		return std::exp(2 * std::log(x) - y) + y * std::exp(-y) - std::exp(x * x) * std::log(x * x + y);
	}
}

int main(int arc, const char* argv[]) {

	return 0;
}
