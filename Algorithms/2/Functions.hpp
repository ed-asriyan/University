//
// Created by ed on 09.04.17.
//

#ifndef LAB2_FUNCTIONS_HPP
#define LAB2_FUNCTIONS_HPP

#include <cmath>
#include <functional>
#include "Equations.hpp"

namespace Functions {
	namespace Store1 {
		double F1(double x);
	}

	namespace Store2 {
		double F1(double x, double y);
		double F2(double x, double y);
		double F3(double x, double y);

		std::function<double(double, double)> Reverse(const std::function<double(double, double)>& func);
		std::function<double(double)> SectionX(const std::function<double(double, double)>& func, double x);
		std::function<double(double)> SectionY(const std::function<double(double, double)>& func, double y);
	}
}

#endif //LAB2_FUNCTIONS_HPP
