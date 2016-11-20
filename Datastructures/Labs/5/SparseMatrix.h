//
// Created by ed on 20.11.16.
//

#ifndef MATRIX_SPARSEMATRIX_H
#define MATRIX_SPARSEMATRIX_H

#include "MatrixBase.h"

namespace Matrix {
	template<class T>
	class SparseMatrix : public MatrixBase<T> {
		private:

		public:
			SparseMatrix(int height, int width);

			/**
			 * @brief Size of the instance in bytes.
			 * @return Instance size.
			 */
			virtual auto get_size() const -> decltype(sizeof(T));

			SparseMatrix<T> operator+(const SparseMatrix<T>&);
			SparseMatrix<T>& operator+=(const SparseMatrix<T>&);
		protected:
			virtual void _set_item(int row, int col, const T& value) override;
			virtual const T& _get_item(int row, int col) const override;
			virtual void _resize() override;
	};

	template<class T>
	void SparseMatrix<T>::_set_item(int row, int col, const T& value) {

	}

	template<class T>
	const T& SparseMatrix<T>::_get_item(int row, int col) const {
		return 1;
	}

	template<class T>
	void SparseMatrix<T>::_resize() {

	}

	template<class T>
	SparseMatrix<T>::SparseMatrix(int height, int width) : MatrixBase<T>(height, width) {

	}

	template<class T>
	SparseMatrix<T>& SparseMatrix<T>::operator+=(const SparseMatrix<T>& b) {
		return *this;
	}

	template<class T>
	SparseMatrix<T> SparseMatrix<T>::operator+(const SparseMatrix<T>& b) {
		SparseMatrix<T> result = *this;
		result += b;
		return result;
	}

	template<class T>
	auto SparseMatrix<T>::get_size() const -> decltype(sizeof(T)) {
		return \
            sizeof(*this) + // struct size
			0;
	}
}

#endif //MATRIX_SPARSEMATRIX_H
