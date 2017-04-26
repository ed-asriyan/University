//
// Created by ed on 09.04.17.
//

#include "Functions.hpp"

double Functions::Store1::F1(double x) {
	return std::sin(M_PI * x / 6);
}

double Functions::Store1::F2(double x) {
	return 1 / (1 + x * x);
}

double Functions::Store2::F1(double x, double y) {
	return std::exp(x * x * x - y) - x * x * x * x * x * x + 2 * (y + 1) * (x * x * x) - y * y - 2 * y - 2;
}

double Functions::Store2::F2(double x, double y) {
	return std::exp(2 * std::log(x) - y) + y * std::exp(-y) - std::exp(x * x) * std::log(x * x + y);
}

double Functions::Store2::F3(double x, double y) {
	return x * x + y;
}

std::function<double(double, double)> Functions::Store2::Reverse(const std::function<double(double, double)>& func) {
	return [&func](double x, double y) {
		return func(y, x);
	};
}

std::function<double(double)> Functions::Store2::SectionX(const std::function<double(double, double)>& func, double x) {
	return [x, func](double y) {
		return func(x, y);
	};
}

std::function<double(double)> Functions::Store2::SectionY(const std::function<double(double, double)>& func, double y) {
	return [y, func](double x) {
		return func(x, y);
	};
}
