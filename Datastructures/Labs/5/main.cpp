#include <iostream>
#include <ctime>
#include <random>

#include "ClassicMatrix.h"
#include "SparseMatrix.h"
#include "Generator.h"

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

	Matrix::SparseMatrix<int> a_sparce(height, width);
	Matrix::SparseMatrix<int> b_sparce(height, width);
	Matrix::SparseMatrix<int> c_sparce(height, width);

	// generate matrix
	if (0 <= g && g <= 1) {
		std::uniform_int_distribution<> item_distribution(1, 10);

		Generator::FillRandom(item_distribution, a_classic, g);
		Generator::FillRandom(item_distribution, b_classic, g);

		static_cast<Matrix::MatrixBase<int>&>(a_sparce) = a_classic;
		static_cast<Matrix::MatrixBase<int>&>(b_sparce) = b_classic;
	} else { // read matrix
		// todo: read matrix
	}

	// run tests
	time_t classic_time = std::clock();
	c_classic = a_classic + b_classic;
	classic_time = std::clock() - classic_time;

	time_t sparse_time = std::clock();
	c_sparce = a_sparce + b_sparce;
	sparse_time = std::clock() - sparse_time;

	// print matrix
	if (height < PRINT_MAX_HEIGHT && width < PRINT_MAX_WIDTH) {
		std::cout << "Matrix A: " << std::endl;
		std::cout << a_classic << std::endl;

		std::cout << "Matrix B: " << std::endl;
		std::cout << b_classic << std::endl;

		std::cout << "Matrix C = A + B: " << std::endl;
		std::cout << c_classic << std::endl;
	}

	// print test result
	std::cout << "Classic matrix (" << a_classic.get_height() << 'x' << a_classic.get_width() << "):" << std::endl;
	std::cout << " Addition time: " << classic_time << std::endl;
	std::cout << " Size of A: " << a_classic.get_size() << std::endl;
	std::cout << " Size of B: " << b_classic.get_size() << std::endl;
	std::cout << " Size of C: " << c_classic.get_size() << std::endl;
	std::cout << std::endl;

	std::cout << "Sparse matrix (" << a_sparce.get_height() << 'x' << a_sparce.get_width() << "):" << std::endl;
	std::cout << " Addition time: " << sparse_time << std::endl;
	std::cout << " Size of A: " << a_sparce.get_size() << std::endl;
	std::cout << " Size of B: " << b_sparce.get_size() << std::endl;
	std::cout << " Size of C: " << c_sparce.get_size() << std::endl;
	std::cout << std::endl;

	return 0;
}