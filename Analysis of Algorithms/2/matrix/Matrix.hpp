//
// Created by Ed Asriyan on 31/10/2017.
//

#ifndef LAB2_MATRIX_HPP
#define LAB2_MATRIX_HPP

#include <stdexcept>
#include <ostream>
#include <algorithm>
#include <iomanip>
#include <cstring>

namespace matrix {
	template<typename T>
	class Matrix {
	public:
		Matrix(const std::initializer_list<const std::initializer_list<const T>>& l)
			: height(l.size()) {
			if (!height) throw std::invalid_argument("initializer_list is empty");
			width = l.begin()->size();

			auto ptr = data = new T* [height];
			for (auto row: l) {
				if (width != row.size()) {
					free();
					throw std::invalid_argument("different length of rows");
				}
				*ptr = new T[width];
				std::copy(row.begin(), row.end(), *(ptr++));
			}
		}

		Matrix(const Matrix& matrix)
			: height(matrix.height), width(matrix.width) {
			data = new T* [width];
			for (int i = 0; i < height; ++i) {
				data[i] = new T[width];
				std::memcpy(data[i], matrix.data[i], width * sizeof(T));
			}
		}

		Matrix(Matrix<T>&& matrix)
			: data(matrix.data), height(matrix.height), width(matrix.width) {
			matrix.data = nullptr;
			matrix.width = 0;
			matrix.data = 0;
		}

		Matrix(size_t rows, size_t cols)
			: height(rows), width(cols) {
			if (!rows) throw std::invalid_argument("Rows count must be positive");
			if (!cols) throw std::invalid_argument("Columns count must be positive");

			data = new T* [height];
			for (size_t i = 0; i < height; ++i) {
				data[i] = new T[width];
			}
		}

		virtual ~Matrix() {
			free();
		}

		template<class T1>
		friend std::ostream& operator<<(std::ostream& out, const Matrix<T1>& matrix) {
			for (size_t i = 0; i < matrix.height; ++i) {
				for (size_t j = 0; j < matrix.width; ++j) {
					const auto row = matrix.data[i];
					out << std::setw(10) << row[j];
				}
				out << std::endl;
			}
			return out;
		}

		const T& operator()(size_t i, size_t j) const {
			if (i >= height) throw std::invalid_argument("i is out of range");
			if (j >= width) throw std::invalid_argument("j is out of range");

			return data[i][j];
		}

		T& operator()(size_t i, size_t j) {
			if (i >= height) throw std::invalid_argument("i must be less then matrix height");
			if (j >= width) throw std::invalid_argument("j must be less then matrix heigh");

			return data[i][j];
		}

		size_t get_rows() const {
			return height;
		}

		size_t get_columns() const {
			return width;
		}

		template<class T1>
		friend Matrix<T1> multiplyClassic(const Matrix<T1>&, const Matrix<T1>&);

		template<class T1>
		friend Matrix<T1> multiplyGrape(const Matrix<T1>&, const Matrix<T1>&);

	private:
		T** data;
		size_t width;
		size_t height;

		void free() {
			if (data) {
				for (size_t i = 0; i < height; ++i) {
					delete data[i];
				}
				delete[] data;
			}
			data = nullptr;
			height = 0;
			width = 0;
		}
	};
}

#endif //LAB2_MATRIX_HPP
