#include <iostream>
#include <ctime>
#include <random>

#include "ClassicMatrix.h"
#include "SparseMatrix.h"
#include "Generator.h"
#include "Helper.h"

#define PRINT_MAX_HEIGHT 20
#define PRINT_MAX_WIDTH 20

int main(int argc, char* argv[]) {
	// default values
	int height = 1000;
	int width = 1000;
	double g = Generator::GetRandomDouble01(0.2, 0.5);

	if (argc == 2) {
		g = std::atof(argv[1]);
	} else if (argc == 3) {
		height = std::atoi(argv[1]);
		width = std::atoi(argv[2]);
	} else if (argc == 4) {
		height = std::atoi(argv[1]);
		width = std::atoi(argv[2]);
		g = std::atof(argv[3]);
	}

	// classic matrix
	Matrix::ClassicMatrix<int> a_classic(height, width);
	Matrix::ClassicMatrix<int> b_classic(height, width);
	Matrix::ClassicMatrix<int> c_classic(height, width);

	Matrix::SparseMatrix<int> a_sparse(height, width);
	Matrix::SparseMatrix<int> b_sparse(height, width);
	Matrix::SparseMatrix<int> c_sparse(height, width);

	// generate matrix
	if (0 <= g && g <= 1) {
		std::uniform_int_distribution<> item_distribution(1, 10);

		Generator::FillRandom(item_distribution, a_classic, g);
		Generator::FillRandom(item_distribution, b_classic, g);

		static_cast<Matrix::MatrixBase<int>&>(a_sparse) = a_classic;
		static_cast<Matrix::MatrixBase<int>&>(b_sparse) = b_classic;
	} else { // read matrix
		// todo: read matrix
	}

	// run tests
	time_t classic_time = std::clock();
	c_classic = a_classic + b_classic;
	classic_time = std::clock() - classic_time;

	time_t sparse_time = std::clock();
	c_sparse = a_sparse + b_sparse;
	sparse_time = std::clock() - sparse_time;

	// print matrix
	if (height < PRINT_MAX_HEIGHT && width < PRINT_MAX_WIDTH) {
		std::cout << "Matrix A (classic & sparse): " << std::endl;
		Helper::ContecateStreamByRows(std::cout, a_classic, a_sparse);
		std::cout << std::endl;

		std::cout << "Matrix B (classic & sparse): " << std::endl;
		Helper::ContecateStreamByRows(std::cout, b_classic, b_sparse);
		std::cout << std::endl;

		std::cout << "Matrix C = A + B (classic & sparse): " << std::endl;
		Helper::ContecateStreamByRows(std::cout, c_classic, c_sparse);
		std::cout << std::endl;
	}

	std::cout << "Equality check:" << std::endl;
	std::cout << " Classic A " << (a_classic == a_sparse ? '=' : '!') << "= sparse A" << std::endl;
	std::cout << " Classic B " << (b_classic == b_sparse ? '=' : '!') << "= sparse B" << std::endl;
	std::cout << " Classic C " << (c_classic == c_sparse ? '=' : '!') << "= sparse C" << std::endl;
	std::cout << std::endl;

	// print test result
	std::cout << "Classic matrix (" << a_classic.get_height() << 'x' << a_classic.get_width() << "):" << std::endl;
	std::cout << " Addition time: " << classic_time << std::endl;
	std::cout << " Size of A: " << a_classic.get_size() << std::endl;
	std::cout << " Size of B: " << b_classic.get_size() << std::endl;
	std::cout << " Size of C: " << c_classic.get_size() << std::endl;
	std::cout << std::endl;

	std::cout << "Sparse matrix (" << a_sparse.get_height() << 'x' << a_sparse.get_width() << "):" << std::endl;
	std::cout << " Addition time: " << sparse_time << std::endl;
	std::cout << " Size of A: " << a_sparse.get_size() << std::endl;
	std::cout << " Size of B: " << b_sparse.get_size() << std::endl;
	std::cout << " Size of C: " << c_sparse.get_size() << std::endl;
	std::cout << std::endl;

	return 0;
}