//
// Created by ed on 13.11.16.
//

#ifndef MATRIX_MATRIXCLASSIC_H
#define MATRIX_MATRIXCLASSIC_H

#include <cstring>

#include "MatrixBase.h"

namespace Matrix {
	template<class T>
	class MatrixClassic : public MatrixBase<T> {
		private:
			T** data = nullptr;

		public:
			/**
			 * @brief Constructor.
			 * @param height Height of the matrix.
			 * @param width Width of hte matrix.
			 */
			MatrixClassic(int width, int height);

			/**
			 * @brief Copy constructor
			 */
			MatrixClassic(const MatrixClassic<T>&);

			/**
			 * @brief Destructor.
			 */
			virtual ~MatrixClassic();

			/**
			 * @brief Size of the instance in bytes.
			 * @return Instance size.
			 */
			virtual auto get_size() const -> decltype(sizeof(T));

			MatrixClassic<T>& operator=(const MatrixClassic<T>& matrix);

			MatrixClassic<T> operator+(const MatrixClassic<T>&);
			MatrixClassic<T>& operator+=(const MatrixClassic<T>&);
		protected:
			virtual T& _get_item(int row, int col) override;
			virtual const T& _get_item(int row, int col) const override;

			virtual void _resize() override;

		private:
			void allocateData();
			void destroyData();

	};

	template<class T>
	MatrixClassic<T>::MatrixClassic(int width, int height) : MatrixBase<T>(width, height) {
		allocateData();
	}

	template<class T>
	MatrixClassic<T>::MatrixClassic(const MatrixClassic<T>& matrix) :MatrixClassic<T>(matrix.get_width(),
	                                                                                  matrix.get_height()) {
		*this = matrix;
	}

	template<class T>
	MatrixClassic<T>::~MatrixClassic() {
		destroyData();
	}

	template<class T>
	auto MatrixClassic<T>::get_size() const -> decltype(sizeof(T)) {
		return \
            sizeof(*this) + // struct size
			sizeof(data[0]) * MatrixBase<T>::get_height() + // size of array of pointers to rows
			sizeof(data[0][0]) * MatrixBase<T>::get_height() * MatrixBase<T>::get_width() + // data size
			0;
	}

	template<class T>
	void MatrixClassic<T>::_resize() {
		allocateData();
	}

	template<class T>
	void MatrixClassic<T>::allocateData() {
		destroyData();

		int height = MatrixBase<T>::get_height();
		int width = MatrixBase<T>::get_width();
		data = new T* [height];
		for (int i = 0; i < height; ++i) {
			data[i] = new T[width];
		}
	}

	template<class T>
	void MatrixClassic<T>::destroyData() {
		if (data == nullptr) return;
		for (int i = MatrixBase<T>::get_height() - 1; i >= 0; --i) {
			delete[] data[i];
		}
		delete[] data;
		data = nullptr;
	}

	template<class T>
	T& MatrixClassic<T>::_get_item(int row, int col) {
		return data[row][col];
	}

	template<class T>
	const T& MatrixClassic<T>::_get_item(int row, int col) const {
		return data[row][col];
	}

	template<class T>
	MatrixClassic<T>& MatrixClassic<T>::operator=(const MatrixClassic<T>& matrix) {
		MatrixBase<T>::operator=(matrix);
		return *this;
	}

	template<class T>
	MatrixClassic<T> MatrixClassic<T>::operator+(const MatrixClassic<T>& b) {
		MatrixClassic<T> result = *this;
		result += b;
		return result;
	}

	template<class T>
	MatrixClassic<T>& MatrixClassic<T>::operator+=(const MatrixClassic<T>& b) {
		int height = MatrixBase<T>::get_height();
		int width = MatrixBase<T>::get_width();

		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				data[i][j] += b.data[i][j];
			}
		}

		return *this;
	}

}
#endif //MATRIX_MATRIXCLASSIC_H
