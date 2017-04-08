//
// Created by ed on 04.04.17.
//

#include <cmath>

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
