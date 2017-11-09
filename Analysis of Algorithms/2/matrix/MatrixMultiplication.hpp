//
// Created by Ed Asriyan on 31/10/2017.
//

#ifndef LAB2_MATRIXMULTIPLICATION_HPP
#define LAB2_MATRIXMULTIPLICATION_HPP

#include <stdexcept>

#include "Matrix.hpp"

namespace matrix {
	namespace _internal {
		inline void throwIfInvalidSize(size_t a_width, size_t b_height) {
			if (a_width != b_height) throw std::invalid_argument("A x B size doesn't match");
		}

		template<class T>
		inline Matrix <T> throwIfInvalidSizeAndCreateResult(
			size_t a_height,
			size_t a_width,
			size_t b_height,
			size_t b_width
		) {
			throwIfInvalidSize(a_width, b_height);
			return Matrix<T>(a_height, b_width);
		}
	}

	template<class T>
	Matrix <T> multiplyClassic(const Matrix <T>& a, const Matrix <T>& b) {
		Matrix<T> result = _internal::throwIfInvalidSizeAndCreateResult<T>(a.height, a.width, b.height, b.width);

		// F: (2 + m*(2 + F{})
		for (int i = 0; i < result.height; i++) {
			// F: (2 + n*(2 + F{})
			for (int j = 0; j < result.width; j++) {
				// F: 3
				result.data[i][j] = 0;

				for (int k = 0; k < b.height; k++) {
					// F: 8
					result.data[i][j] += a.data[i][k] * b.data[k][j];
				}
			}
		}

		return result;
	}

	template<class T>
	Matrix <T> multiplyGrape(const Matrix <T>& a, const Matrix <T>& b) {
		Matrix<T> result = _internal::throwIfInvalidSizeAndCreateResult<T>(a.height, a.width, b.height, b.width);

		size_t a_height = a.height;
		size_t a_width = a.width;
		size_t b_width = b.width;

		T* mul_h = new T[a_height];
		T* mul_w = new T[b_width];

		// F: 2 + m(2 + F{})
		for (int i = 0; i < a_height; i++) {
			// F: 1
			mul_h[i] = 0;
			// F: 3 + n/2(3 + F{})
			for (int j = 0; j < a_width / 2; j++) {
				// F: 12
				//   1  1      1  1            1   2   1            1    3
				mul_h[i] = mul_h[i] + a.data[i][2 * j] * a.data[i][2 * j + 1];
			}

		}

		// F: 2 + q(2 + F{})
		for (int i = 0; i < b_width; i++) {
			// F: 1
			mul_w[i] = 0;
			// F: 3 + n/2(3 + F{})
			for (int j = 0; j < a_width / 2; j++) {
				// F: 12
				//   1  1      1  1             2   1  1              3    1
				mul_w[i] = mul_w[i] + b.data[2 * j][i] * b.data[2 * j + 1][i];
			}
		}

		// F: 2 + m(2 + F{})
		for (int i = 0; i < a_height; i++) {
			// F: 2 + q(2 + F{})
			for (int j = 0; j < b_width; j++) {
				// F: 7
				result.data[i][j] = -mul_h[i] - mul_w[j];
				// F: 3 + n/2(3 + F{})
				for (int k = 0; k < a_width / 2; k++) {
					// F: 21
					//         1  1  1            1  1  1             1   2   1              3    1   1             1    3    1             2   1
					result.data[i][j] = result.data[i][j] + (a.data[i][k * 2] + b.data[k * 2 + 1][j])
						* (a.data[i][2 * k + 1] + b.data[2 * k][j]);
				}
			}
		}

		// F: 1
		if (a_width % 2) {
			// F: 2 + m(2 + F{})
			for (int i = 0; i < a_height; i++) {
				// F: 2 + q(2 + F{})
				for (int j = 0; j < b_width; j++) {
					// F: 13
					//         1  1  1            1  1  1            1   2   1             2   1
					result.data[i][j] = result.data[i][j] + a.data[i][a_width - 1] * b.data[a_width - 1][j];
				}
			}
		}

		delete[] mul_w;
		delete[] mul_h;

		return result;
	}

	template<class T>
	Matrix <T> multiplyGrapeOptimized(const Matrix <T>& a, const Matrix <T>& b) {
		Matrix<T> result = _internal::throwIfInvalidSizeAndCreateResult<T>(a.height, a.width, b.height, b.width);

		size_t a_height = a.height;
		size_t a_width = a.width;
		size_t b_width = b.width;

		T* mul_h = new T[a_height];
		T* mul_w = new T[b_width];

		// F: 2 + m(2 + F{})
		for (int i = 0; i < a_height; i++) {
			// F: 1
			mul_h[i] = 0;
			// F: 3 + n/2(3 + F{})
			for (int j = 0; j < a_width / 2; j++) {
				// F: 12
				//   1  1      1  1            1   2   1            1    3
				mul_h[i] = mul_h[i] + a.data[i][2 * j] * a.data[i][2 * j + 1];
			}

		}

		// F: 2 + q(2 + F{})
		for (int i = 0; i < b_width; i++) {
			// F: 1
			mul_w[i] = 0;
			// F: 3 + n/2(3 + F{})
			for (int j = 0; j < a_width / 2; j++) {
				// F: 12
				//   1  1      1  1             2   1  1              3    1
				mul_w[i] = mul_w[i] + b.data[2 * j][i] * b.data[2 * j + 1][i];
			}
		}

		// F: 2 + m(2 + F{})
		for (int i = 0; i < a_height; i++) {
			// F: 2 + q(2 + F{})
			for (int j = 0; j < b_width; j++) {
				// F: 7
				result.data[i][j] = -mul_h[i] - mul_w[j];
				// F: 3 + n/2(3 + F{})
				for (int k = 0; k < a_width / 2; k++) {
					// F: 21
					//         1  1  1            1  1  1             1   2   1              3    1   1             1    3    1             2   1
					result.data[i][j] = result.data[i][j] + (a.data[i][k * 2] + b.data[k * 2 + 1][j])
						* (a.data[i][2 * k + 1] + b.data[2 * k][j]);
				}
			}
		}

		// F: 1
		if (a_width % 2) {
			// F: 2 + m(2 + F{})
			for (int i = 0; i < a_height; i++) {
				// F: 2 + q(2 + F{})
				for (int j = 0; j < b_width; j++) {
					// F: 13
					//         1  1  1            1  1  1            1   2   1             2   1
					result.data[i][j] = result.data[i][j] + a.data[i][a_width - 1] * b.data[a_width - 1][j];
				}
			}
		}

		delete[] mul_w;
		delete[] mul_h;

		return result;
	}
}

#endif //LAB2_MATRIXMULTIPLICATION_HPP
