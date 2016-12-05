//
// Created by ed on 20.11.16.
//

#ifndef MATRIX_GENERATOR_H
#define MATRIX_GENERATOR_H

#include <random>
#include <algorithm>

#include "MatrixBase.h"

namespace Generator {
	/**
	 * @brief Template byte-distribution.
	 */
	template<class T>
	class ObjectDistribution {
		public:
			ObjectDistribution() = default;

			template<class GENERATOR>
			T operator()(GENERATOR& generator) const {
				BYTE* resultPtr = new BYTE[sizeof(T) / sizeof(BYTE)];

				operator()(generator, (T*) resultPtr);

				T result = *(T*) resultPtr;
				delete[] resultPtr;

				return result;
			};

			template<class GENERATOR>
			void operator()(GENERATOR& generator, T* object) const {
				BYTE* resultPtr = (BYTE*) object;

				for (int i = 0; i < sizeof(T); i++) {
					resultPtr[i] = generator();
				}
			};

		private:
			typedef char BYTE;
	};

	/**
	 * @brief Fill the matrix by random items
	 * @param distr Random distribution
	 * @param matrix Matrix to fill
	 * @param fill_factor Non-zero elements number in percents.
	 */
	template<class T, class DISTRIBUTION>
	void FillRandom(DISTRIBUTION distr, Matrix::MatrixBase<T>& matrix, double fill_factor) {
		int height = matrix.get_height();
		int width = matrix.get_width();
		int items_count = static_cast<int>(height * width * fill_factor);

		std::random_device rd;

		int* rows = new int[height];
		int* cols = new int[width];

		std::iota(rows, rows + height, 0);
		std::iota(cols, cols + width, 0);

		for (int i = 0; i < items_count; ++i) {
			auto _height = i % height;
			auto _width = i % width;

			if (!_height) {
				std::shuffle(rows, rows + height, rd);
			}
			if (!_width) {
				std::shuffle(cols, cols + width, rd);
			}

			matrix.set_item(rows[_height], cols[_width], distr(rd));
		}

		delete[] cols;
		delete[] rows;
	}

	/**
	 * @brief Generates random double in range from min to max.
	 * @param min Lower border.
	 * @param max Higher border.
	 * @return Random double in range from min to max.
	 */
	double GetRandomDouble01(double min = 0, double max = 1) {
		std::random_device rd;
		std::mt19937 e2(rd());
		std::uniform_real_distribution<> dist(min, max);
		return dist(e2);
	}
}

#endif //MATRIX_GENERATOR_H
