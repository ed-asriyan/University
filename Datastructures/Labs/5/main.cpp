#include <iostream>
#include <ctime>
#include <random>

#include "ClassicMatrix.h"
#include "SparseMatrix.h"
#include "Generator.h"
#include "Helper.h"

#define PRINT_MAX_HEIGHT 20
#define PRINT_MAX_WIDTH 20

template<class T>
void PrintAndCompareMatrix(std::ostream& out, Matrix::ClassicMatrix<T>& classic, Matrix::SparseMatrix<T>& sparse) {
	Helper::ContecateStreamByRows(std::cout, classic, sparse);

	out << "Data: ";
	for (auto& item: sparse.get_data()) {
		out << item << ' ';
	}
	out << std::endl;

	out << "Rows: ";
	for (auto& item: sparse.get_rows()) {
		out << "(" << item.index << ", " << item.row << ") ";
	}
	out << std::endl;

	out << "Columns: ";
	for (auto& item: sparse.get_rows()) {
		out << &item << ' ';
	}
	out << std::endl;

	out << std::endl;
}

int main(int argc, char* argv[]) {
	// default values
	int height = 1000;
	int width = 1000;
	double g = -2;

	// handling arguments
	if (argc == 2) {
		g = std::atof(argv[1]);
	} else if (argc == 3) {
		g = std::atoi(argv[1]);
		height = width = std::atoi(argv[2]);
	} else if (argc == 4) {
		g = std::atof(argv[1]);
		height = std::atoi(argv[2]);
		width = std::atoi(argv[3]);
	}

	// classic matrix
	Matrix::ClassicMatrix<int> a_classic(height, width);
	Matrix::ClassicMatrix<int> b_classic(height, width);
	Matrix::ClassicMatrix<int> c_classic(height, width);

	// sparse matrix
	Matrix::SparseMatrix<int> a_sparse(height, width);
	Matrix::SparseMatrix<int> b_sparse(height, width);
	Matrix::SparseMatrix<int> c_sparse(height, width);

	// read matrix
	if (-1 > g || g > 1) {
		std::cout << "Reading matrix..." << std::endl;

		std::cin >> a_classic;
		std::cin >> b_classic;

		height = a_classic.get_height();
		width = a_classic.get_width();

		if (height != b_classic.get_height() || width != b_classic.get_width()) {
			std::cerr << "Invalid matrix size: matrix sizes must be equal." << std::endl;
			return -1;
		}
	} else { // generate matrix
		std::cout << "Generating matrix (g = " << g << ")..." << std::endl;

		std::uniform_int_distribution<> item_distribution(1, 10);

		Generator::FillRandom(item_distribution, a_classic, g);
		Generator::FillRandom(item_distribution, b_classic, g);
	}

	static_cast<Matrix::MatrixBase<int>&>(a_sparse) = a_classic;
	static_cast<Matrix::MatrixBase<int>&>(b_sparse) = b_classic;
	// run tests
	std::cout << "Adding matrix..." << std::endl;

	time_t classic_time = std::clock();
	c_classic = a_classic + b_classic;
	classic_time = std::clock() - classic_time;

	time_t sparse_time = std::clock();
	c_sparse = a_sparse + b_sparse;
	sparse_time = std::clock() - sparse_time;

	// work is done
	std::cout << "Done!" << std::endl << std::endl;

	// print matrix
	if (height < PRINT_MAX_HEIGHT && width < PRINT_MAX_WIDTH) {
		std::cout << "Matrix A (classic & sparse): " << std::endl;
		PrintAndCompareMatrix(std::cout, a_classic, a_sparse);

		std::cout << "Matrix B (classic & sparse): " << std::endl;
		PrintAndCompareMatrix(std::cout, b_classic, b_sparse);

		std::cout << "Matrix C = A + B (classic & sparse): " << std::endl;
		PrintAndCompareMatrix(std::cout, c_classic, c_sparse);
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