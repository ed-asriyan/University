#include <iostream>

#include "matrix/Matrix.hpp"
#include "matrix/MatrixMultiplication.hpp"

int main() {
	matrix::Matrix<int> a(
		{
			{1, 2, 3},
			{4, 5, 6},
			{7, 8, 9},
		}
	);
	matrix::Matrix<int> b(
		{
			{0,0,1},
			{0,1,0},
			{1,0,0},
		}
	);

	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << matrix::multiplyClassic(a, b) << std::endl;
	std::cout << matrix::multiplyGrape(a, b) << std::endl;
	std::cout << matrix::multiplyGrapeOptimized(a, b) << std::endl;

	return 0;
}
