//
// Created by ed on 18.04.17.
//

#ifndef LAB2_TEST_HPP
#define LAB2_TEST_HPP

#include <iostream>

#include "Vector.hpp"

template<class T>
void test(std::ostream& out, const Vector<T>& a, const Vector<T>& b, T c) {
	out << "Vector a: " << a << std::endl;
	out << "Vector b: " << b << std::endl;
	out << std::endl;

	out << "Vector a + b: " << a + b << std::endl;
	out << "Vector a - b: " << a - b << std::endl;
	out << "Scalar a * b: " << a * b << std::endl;
	out << "Vector a / " << c << ": " << a / c << std::endl;
	out << "Vector a * " << c << ": " << a * c << std::endl;
	out << "Vector b * " << c << ": " << b * c << std::endl;
}

#endif //LAB2_TEST_HPP
