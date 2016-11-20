//
// Created by ed on 13.11.16.
//

#ifndef MATRIX_MATRIXBASE_H
#define MATRIX_MATRIXBASE_H

#include <exception>
#include <ostream>
#include <istream>
#include <iomanip>

namespace Matrix {
	class InvalidMatrixSizeException : public std::exception {};

	class InvalidItemPositionException : public std::exception {};

	template<class T>
	class MatrixBase {
		private:
			int height;
			int width;

		public:
			/**
			 * @brief Constructor.
			 * @param height Height of the matrix.
			 * @param width Width of hte matrix.
			 */
			MatrixBase(int height, int width);

			/**
			 * @brief Copy constructor
			 */
			MatrixBase(const MatrixBase<T>&) = default;

			/**
			 * @brief Destructor.
			 */
			virtual ~MatrixBase();

			/**
			 * @brief Resizes the matrix to new size.
			 * @param new_height New matrix height.
			 * @param new_width New matrix width.
			 */
			void Resize(int new_height, int new_width);

			/**
			 * @brief Matrix item.
			 * @param row Number of row, which contains the requiring item.
			 * @param col Number of column, which contains the requiring item.
			 * @return Link to the item.
			 */
			T& get_item(int row, int col);

			/**
			 * @brief Matrix item.
			 * @param row Number of row, which contains the requiring item.
			 * @param col Number of column, which contains the requiring item.
			 * @return Link to the const item.
			 */
			const T& get_item(int row, int col) const;

			/**
			 * @brief Size of the instance in bytes.
			 * @return Instance size.
			 */
			virtual auto get_size() const -> decltype(sizeof(this)) = 0;

			/**
			 * @brief Returns matrix width.
			 * @return Matrix width.
			 */
			int get_width() const;

			/**
			 * @brief Returns matrix height.
			 * @return Matrix height.
			 */
			int get_height() const;

			template<class I>
			friend std::ostream& operator<<(std::ostream& os, const MatrixBase<I>& base);

			template<class I>
			friend std::istream& operator>>(std::istream& is, MatrixBase<I>& base);

			MatrixBase<T>& operator=(const MatrixBase<T>& b);

			bool operator==(const MatrixBase<T>&) const;
			bool operator!=(const MatrixBase<T>&) const;

		protected:
			virtual T& _get_item(int row, int col) = 0;
			virtual const T& _get_item(int row, int col) const = 0;

			virtual void _resize() = 0;
	};

	template<class T>
	MatrixBase<T>::MatrixBase(int height, int width) : height(height), width(width) {
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

	template<class T>
	std::istream& operator>>(std::istream& is, MatrixBase<T>& base) {
		for (int i = 0; i < base.height; ++i) {
			for (int j = 0; j < base.width; ++j) {
				is >> base.get_item(i, j);
			}
		}
		return is;
	}

	template<class T>
	void MatrixBase<T>::Resize(int new_height, int new_width) {
		if (height != new_height || width != new_width) {
			if (new_height < 0 || new_width < 0) {
				throw InvalidMatrixSizeException();
			}
			height = new_height;
			width = new_width;
			_resize();
		}
	}

	template<class T>
	MatrixBase<T>::~MatrixBase() {

	}

	template<class T>
	MatrixBase<T>& MatrixBase<T>::operator=(const MatrixBase<T>& b) {
		Resize(b.get_height(), b.get_width());
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				get_item(i, j) = b.get_item(i, j);
			}
		}
		return *this;
	}

	template<class T>
	bool MatrixBase<T>::operator==(const MatrixBase<T>& b) const {
		if (height != b.height || width != b.width) {
			return false;
		}

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (get_item(i, j) != b.get_item(i, j)) {
					return false;
				}
			}
		}

		return true;
	}

	template<class T>
	bool MatrixBase<T>::operator!=(const MatrixBase<T>& b) const {
		return !(*this == b);
	}

	template<class A, class B, class C>
	void add(const MatrixBase<A>& a, const MatrixBase<B>& b, MatrixBase<C>& c) {
		int height = a.get_height();
		int width = a.get_width();

		if (height != b.get_height() || width != b.get_width()) {
			throw InvalidMatrixSizeException();
		}

		c.Resize(height, width);

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				c.get_item(i, j) = a.get_item(i, j) + b.get_item(i, j);
			}
		}
	};

}
#endif //MATRIX_MATRIXBASE_H
