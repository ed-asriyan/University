//
// Created by ed on 20.11.16.
//

#ifndef MATRIX_SPARSEMATRIX_H
#define MATRIX_SPARSEMATRIX_H

#include <vector>
#include <list>
#include <ostream>

#include "MatrixBase.h"

namespace Matrix {
	/**
	 * @brief Sparse matrix
	 */
	template<class T>
	class SparseMatrix : public MatrixBase<T> {
		private:
			T neutral_elem = T();

			/**
			 * Non-zero elements.
			 */
			std::vector<T> data;

			/**
			 * Row element type.
			 */
			struct RowItem {
				unsigned long index;
				int row;
			};

			/**
			 * List of iterator to the item in data.
			 */
			std::list<RowItem> rows;

			/**
			 * Vector of iterator to the first row element of the i column/
			 */
			std::vector<decltype(rows.begin())> columns;

			auto findRowIterator(int row, int col) -> decltype(rows.begin());
			auto findRowIterator(int row, int col) const -> decltype(rows.cbegin());

		public:
			/**
			 * @brief Constructor.
			 * @param height Height of the matrix.
			 * @param width Width of hte matrix.
			 */
			SparseMatrix(int height, int width);

			/**
			 * @brief Copy constructor.
			 */
			SparseMatrix(const SparseMatrix<T>&);

			/**
			 * @brief Size of the instance in bytes.
			 * @return Instance size.
			 */
			virtual auto get_size() const -> decltype(sizeof(T));

			/**
			 * @brief Returns data.
			 * @return Data.
			 */
			const std::vector<T>& get_data() const;

			/**
			 * @brief Returns rows.
			 * @return Rows.
			 */
			const std::list<RowItem>& get_rows() const;

			/**
			 * @brief Returns columns.
			 * @return Columns.
			 */
			auto get_columns() const -> const decltype(&columns);

			SparseMatrix<T>& operator=(const SparseMatrix<T>&);

			SparseMatrix<T> operator+(const SparseMatrix<T>&) const;
			SparseMatrix<T>& operator+=(const SparseMatrix<T>&);

		protected:
			virtual void _set_item(int row, int col, const T& value) override;
			virtual const T& _get_item(int row, int col) const override;
			virtual void _resize() override;
	};

	template<class T>
	SparseMatrix<T>::SparseMatrix(int height, int width) : MatrixBase<T>(height, width) {
		_resize();
	}

	template<class T>
	SparseMatrix<T>::SparseMatrix(const SparseMatrix<T>& matrix) : SparseMatrix<T>(matrix.get_height(),
	                                                                               matrix.get_width()) {
		*this = matrix;
	}

	template<class T>
	void SparseMatrix<T>::_set_item(int row, int col, const T& value) {
		auto it = findRowIterator(row, col);
		if (it != rows.end()) {
			data[it->index] = value;
		} else {
			if (value != neutral_elem) {
				auto row_ref = columns[col];
				auto new_it = rows.insert(row_ref, RowItem{data.size(), row});
				data.push_back(value);
				for (int i = col - 1; i >= 0; --i) {
					if (columns[i] == row_ref) {
						columns[i] = new_it;
					} else {
						break;
					}
				}
				columns[col] = new_it;
			}
		}
	}

	template<class T>
	const T& SparseMatrix<T>::_get_item(int row, int col) const {
		const auto it = findRowIterator(row, col);
		return it != rows.end() ? data[it->index] : neutral_elem;
	}

	template<class T>
	void SparseMatrix<T>::_resize() {
		rows.clear();
		auto rows_end = rows.end();
		columns.resize((unsigned long) MatrixBase<T>::get_width() + 1);
		for (auto& item: columns) {
			item = rows_end;
		}
	}

	template<class T>
	SparseMatrix<T>& SparseMatrix<T>::operator+=(const SparseMatrix<T>& b) {
		const int height = MatrixBase<T>::get_height();
		const int width = MatrixBase<T>::get_width();
		if (height != b.get_height() || width != b.get_width()) {
			throw InvalidMatrixSizeException();
		}

		for (int i = 0; i < width; ++i) {
			auto next_row = b.columns[i + 1];
			for (auto bt = b.columns[i]; bt != next_row; ++bt) {
				_set_item(bt->row, i, _get_item(bt->row, i) + bt->value);
			}
		}

		return *this;
	}

	template<class T>
	SparseMatrix<T> SparseMatrix<T>::operator+(const SparseMatrix<T>& b) const {
		SparseMatrix<T> result = *this;
		add(*this, b, result);
		return result;
	}

	template<class T>
	auto SparseMatrix<T>::get_size() const -> decltype(sizeof(T)) {
		return \
            sizeof(*this) + // struct size
			sizeof(*(data.begin())) * data.size() + // data items
			sizeof(*(rows.begin())) * rows.size() + // rows items
			sizeof(*(columns.begin())) * columns.size() + // columns size
			0;
	}

	template<class T>
	auto SparseMatrix<T>::findRowIterator(int row, int col) -> decltype(rows.begin()) {
		auto next_col = columns[col + 1];
		for (auto it = columns[col]; it != next_col; ++it) {
			if (it->row == row) {
				return it;
			}
		}
		return rows.end();
	}

	template<class T>
	auto SparseMatrix<T>::findRowIterator(int row, int col) const -> decltype(rows.cbegin()) {
		typename std::list<RowItem>::const_iterator next_col = columns[col + 1];
		for (typename std::list<RowItem>::const_iterator it = columns[col]; it != next_col; ++it) {
			if (it->row == row) {
				return it;
			}
		}
		return rows.cend();
	}

	template<class T>
	SparseMatrix<T>& SparseMatrix<T>::operator=(const SparseMatrix<T>& matrix) {
		const int height = matrix.get_height();
		const int width = matrix.get_width();

		MatrixBase<T>::Resize(height, width);

		for (int i = 0; i < width; ++i) {
			auto next_row = matrix.columns[i + 1];
			for (auto bt = matrix.columns[i]; bt != next_row; ++bt) {
				_set_item(bt->row, i, matrix.data[bt->index]);
			}
		}

		return *this;
	}

	template<class T>
	const std::vector<T>& SparseMatrix<T>::get_data() const {
		return data;
	}

	template<class T>
	const std::list<typename SparseMatrix<T>::RowItem>& SparseMatrix<T>::get_rows() const {
		return rows;
	}

	template<class T>
	auto SparseMatrix<T>::get_columns() const -> const decltype(&columns) {
		return columns;
	}
}

#endif //MATRIX_SPARSEMATRIX_H
