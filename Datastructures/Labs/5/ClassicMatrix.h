//
// Created by ed on 13.11.16.
//

#ifndef MATRIX_CLASSICMATRIX_H
#define MATRIX_CLASSICMATRIX_H

#include <cstring>

#include "MatrixBase.h"

namespace Matrix {
	template<class T>
	class ClassicMatrix : public MatrixBase<T> {
		private:
			T** data = nullptr;

			int _height;
		public:
			/**
			 * @brief Constructor.
			 * @param height Height of the matrix.
			 * @param width Width of hte matrix.
			 */
			ClassicMatrix(int width, int height);

			/**
			 * @brief Copy constructor
			 */
			ClassicMatrix(const ClassicMatrix<T>&);

			/**
			 * @brief Destructor.
			 */
			virtual ~ClassicMatrix();

			/**
			 * @brief Size of the instance in bytes.
			 * @return Instance size.
			 */
			virtual auto get_size() const -> decltype(sizeof(T));

			ClassicMatrix<T>& operator=(const ClassicMatrix<T>& matrix);

			ClassicMatrix<T> operator+(const ClassicMatrix<T>&);
			ClassicMatrix<T>& operator+=(const ClassicMatrix<T>&);
		protected:
			virtual void _set_item(int row, int col, const T& value) override;
			virtual const T& _get_item(int row, int col) const override;

			virtual void _resize() override;

		private:
			void allocateData();
			void destroyData();

	};

	template<class T>
	ClassicMatrix<T>::ClassicMatrix(int width, int height) : MatrixBase<T>(width, height) {
		allocateData();
	}

	template<class T>
	ClassicMatrix<T>::ClassicMatrix(const ClassicMatrix<T>& matrix) :ClassicMatrix<T>(matrix.get_width(),
	                                                                                  matrix.get_height()) {
		*this = matrix;
	}

	template<class T>
	ClassicMatrix<T>::~ClassicMatrix() {
		destroyData();
	}

	template<class T>
	auto ClassicMatrix<T>::get_size() const -> decltype(sizeof(T)) {
		return \
            sizeof(*this) + // struct size
			sizeof(data[0]) * MatrixBase<T>::get_height() + // size of array of pointers to rows
			sizeof(data[0][0]) * MatrixBase<T>::get_height() * MatrixBase<T>::get_width() + // data size
			0;
	}

	template<class T>
	void ClassicMatrix<T>::_resize() {
		allocateData();
	}

	template<class T>
	void ClassicMatrix<T>::allocateData() {
		destroyData();

		int height = MatrixBase<T>::get_height();
		int width = MatrixBase<T>::get_width();
		data = new T* [height];
		for (int i = 0; i < height; ++i) {
			data[i] = new T[width];
			for (int j = 0; j < width; ++j) {
				data[i][j] = T();
			}
		}
		_height = height;
	}

	template<class T>
	void ClassicMatrix<T>::destroyData() {
		if (data == nullptr) return;
		for (int i = _height - 1; i >= 0; --i) {
			delete[] data[i];
		}
		delete[] data;
		data = nullptr;
	}

	template<class T>
	void ClassicMatrix<T>::_set_item(int row, int col, const T& value) {
		data[row][col] = value;
	}

	template<class T>
	const T& ClassicMatrix<T>::_get_item(int row, int col) const {
		return data[row][col];
	}

	template<class T>
	ClassicMatrix<T>& ClassicMatrix<T>::operator=(const ClassicMatrix<T>& matrix) {
		MatrixBase<T>::operator=(matrix);
		return *this;
	}

	template<class T>
	ClassicMatrix<T> ClassicMatrix<T>::operator+(const ClassicMatrix<T>& b) {
		ClassicMatrix<T> result = *this;
		result += b;
		return result;
	}

	template<class T>
	ClassicMatrix<T>& ClassicMatrix<T>::operator+=(const ClassicMatrix<T>& b) {
		int height = MatrixBase<T>::get_height();
		int width = MatrixBase<T>::get_width();

		if (height != b.get_height() || width != b.get_width()) {
			throw InvalidMatrixSizeException();
		}

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				data[i][j] += b.data[i][j];
			}
		}

		return *this;
	}

}
#endif //MATRIX_CLASSICMATRIX_H
