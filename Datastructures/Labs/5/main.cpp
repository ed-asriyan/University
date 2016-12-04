#include <iostream>
#include <ctime>
#include <random>

#include "ClassicMatrix.h"
#include "SparseMatrix.h"
#include "Generator.h"
#include "Helper.h"

#define PRINT_MAX_HEIGHT 20
#define PRINT_MAX_WIDTH 20

/**
 * @brief Reads element matrix from std::cin until the OES
 * @param matrix Matrix to write in.
 */
template<class T>
void ReadMatrixElements(Matrix::MatrixBase<T>& matrix) {
	auto matrix_height = matrix.get_height();
	auto matrix_width = matrix.get_width();

	while (!std::cin.eof()) {
		// read element row
		int row = 0;
		while (true) {
			std::cout << "Enter row:";
			std::cin >> row;
			if (row < 0 || row >= matrix_height) {
				std::cout << "\tError: value is out of range. Valid values: [0, " << matrix_height - 1 << "]."
				          << std::endl;
			} else {
				break;
			}
		}

		// read element column
		int col = 0;
		while (true) {
			std::cout << "Enter column:";
			std::cin >> row;
			if (col < 0 || col >= matrix_width) {
				std::cout << "\tError: value is out of range. Valid values: [0, " << matrix_width - 1 << "]."
				          << std::endl;
			} else {
				break;
			}
		}

		// read value
		T value;
		std::cout << "Enter value: ";
		std::cin >> value;
		matrix.set_item(col, row, value);
	}
}

/**
 * @brief Reads all matrix elements.
 * @param matrix Matrix to write in.
 */
template<class T>
void ReadMatrix(Matrix::MatrixBase<T>& matrix) {
	auto matrix_height = matrix.get_height();
	auto matrix_width = matrix.get_width();

	for (int i = 0; i < matrix_height; ++i) {
		for (int j = 0; j < matrix_width; ++j) {
			T value;
			std::cin >> value;
			matrix.set_item(i, j, value);
		}
	}
}

/**
 * @brief Reads matrix from std::cin.
 * @param matrix Matrix to write in
 */
template<class T>
void ReadMatrixDialog(Matrix::MatrixBase<T>& matrix, bool fixed_size = false) {
	// matrix size
	int height;
	int width;
	if (fixed_size) {
		height = matrix.get_height();
		width = matrix.get_width();
	} else {
		std::cout << "Enter height: ";
		std::cin >> height;
		std::cout << "Enter width: ";
		std::cin >> width;
		matrix.Resize(height, width);
	}

	bool select_mode;
	std::cout << "Use selection mode? (0, 1): ";
	std::cin >> select_mode;

	if (select_mode) {
		while (true) {
			int row = 0;
			while (true) {
				std::cout << "Enter row (negative to stop): ";
				std::cin >> row;
				if (row >= height) {
					std::cout << "Value is out of range (must be less then " << height << ")." << std::endl;
				} else {
					break;
				}
			}
			if (row < 0) {
				break;
			}

			int col = 0;
			while (true) {
				std::cout << "Enter column (negative to stop): ";
				std::cin >> col;
				if (col >= width) {
					std::cout << "Value is out of range (must be less then " << width << ")." << std::endl;
				} else {
					break;
				}
			}
			if (col < 0) {
				break;
			}

			T value;
			std::cout << "Enter value: ";
			std::cin >> value;

			matrix.set_item(row, col, value);
		}
	} else {
		ReadMatrix(matrix);
	}

}

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

	out << std::endl;
}

int main(int argc, char* argv[]) {
	// default values
	int height = 1000;
	int width = 1000;
	double fill_factor = -2;
	bool user_dialog = false;
	bool generate = false;

	// handling arguments
	if (argc == 2) {
		if (std::string(argv[1]) == "-ui") {
			user_dialog = true;
			generate = false;
		} else {
			fill_factor = std::atof(argv[1]);
			generate = true;
		}
	} else if (argc == 3) {
		fill_factor = std::atoi(argv[1]);
		height = width = std::atoi(argv[2]);
		generate = true;
	} else if (argc == 4) {
		fill_factor = std::atof(argv[1]);
		height = std::atoi(argv[2]);
		width = std::atoi(argv[3]);
		generate = true;
	}

	// classic matrix
	Matrix::ClassicMatrix<int> a_classic(height, width);
	Matrix::ClassicMatrix<int> b_classic(height, width);
	Matrix::ClassicMatrix<int> c_classic(height, width);

	// sparse matrix
	Matrix::SparseMatrix<int> a_sparse(height, width);
	Matrix::SparseMatrix<int> b_sparse(height, width);
	Matrix::SparseMatrix<int> c_sparse(height, width);

	// generate matrix
	if (generate) {
		std::cout << "Generating matrix (fill factor is " << fill_factor << ")..." << std::endl;

		std::uniform_int_distribution<> item_distribution(1, 10);

		Generator::FillRandom(item_distribution, a_classic, fill_factor);
		Generator::FillRandom(item_distribution, b_classic, fill_factor);
	} else { // read
		std::cout << "Reading matrix..." << std::endl;

		// with ui
		if (user_dialog) {
			std::cout << "Matrix A:" << std::endl;
			ReadMatrixDialog(a_classic, false);

			b_classic.Resize(a_classic.get_height(), a_classic.get_width());

			std::cout << "Matrix B:" << std::endl;
			ReadMatrixDialog(b_classic, true);
		} else { // from input stream
			std::cin >> a_classic;
			std::cin >> b_classic;
		}
		height = a_classic.get_height();
		width = a_classic.get_width();

		if (a_classic.get_height() != b_classic.get_height() || a_classic.get_width() != b_classic.get_width()) {
			std::cerr << "Invalid matrix size: matrix sizes must be equal." << std::endl;
			return -1;
		}
	}

	// copy matrix
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