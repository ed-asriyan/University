//
// Created by ed on 13.11.16.
//

#ifndef MATRIX_MATRIXBASE_H
#define MATRIX_MATRIXBASE_H

#include <exception>
#include <ostream>
#include <iomanip>

namespace Matrix {
	class InvalidMatrixSizeException : public std::exception {};

	class InvalidItemPositionException : public std::exception {};

	template<class T>
	class MatrixBase {

		private:
			int width;

			int height;
		public:
			MatrixBase(int width, int height);

			T& get_item(int row, int col);
			const T& get_item(int row, int col) const;

			virtual auto get_size() const -> decltype(sizeof(T)) = 0;

			int get_width() const;
			int get_height() const;

			template<class I>
			friend std::ostream& operator<<(std::ostream& os, const MatrixBase<I>& base);

		protected:
			virtual T& _get_item(int row, int col) = 0;
			virtual const T& _get_item(int row, int col) const = 0;
	};

	template<class T>
	MatrixBase<T>::MatrixBase(int width, int height) : width(width), height(height) {
		if (width < 0 || height < 0) {
			throw InvalidMatrixSizeException();
		}
	}

	template<class T>
	T& MatrixBase<T>::get_item(int row, int col) {
		if (row < 0 || row >= height || col < 0 || col >= width) {
			throw InvalidItemPositionException();
		}
		return _get_item(col, row);
	}

	template<class T>
	const T& MatrixBase<T>::get_item(int row, int col) const {
		if (row < 0 || row >= height || col < 0 || col >= width) {
			throw InvalidItemPositionException();
		}
		return _get_item(col, row);
	}

	template<class T>
	int MatrixBase<T>::get_width() const {
		return width;
	}

	template<class T>
	int MatrixBase<T>::get_height() const {
		return height;
	}

	template<class T>
	std::ostream& operator<<(std::ostream& os, const MatrixBase<T>& base) {
		auto height = base.get_height();
		auto width = base.get_width();

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				os << std::setw(3) << base.get_item(i, j);
			}
			os << std::endl;
		}
		return os;
	}

	template<class A, class B, class C>
	void multiply(const MatrixBase<A>& a, const MatrixBase<B>& b, MatrixBase)

}
#endif //MATRIX_MATRIXBASE_H
