#include <iostream>

#include "test.hpp"

int main() {
	Vector<double> a = {0.1, 0.2, 0.3, 0.4, 0.5};
	Vector<double> b = {0.6, 0.7, 0.8, 0.9, 1.0};
	double c = 2;

	test(std::cout, a, b, c);

	return 0;
}