//
// Created by ed on 20.11.16.
//

#ifndef MATRIX_GENERATOR_H
#define MATRIX_GENERATOR_H

#include <cmath>
#include <random>

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
	 * @param g Sparce power
	 */
	template<class T, class DISTRIBUTION>
	void FillRandom(DISTRIBUTION distr, Matrix::MatrixBase<T>& matrix, double g = 1) {
		int height = matrix.get_height();
		int width = matrix.get_width();

		int items_count = (g >= 0 && g < 1) ? (int) std::pow((double) height * width, (1.0 + g) / 2) : height * width;

		std::random_device rd;
		std::uniform_int_distribution<int> height_distr(0, height - 1);
		std::uniform_int_distribution<int> width_distr(0, width - 1);

		T default_item;
		while (items_count) {
			int row = height_distr(rd);
			int col = width_distr(rd);

			auto& item = matrix.get_item(row, col);
			T value = distr(rd);

			if (item == default_item) {
				matrix.set_item(row, col, value);
				--items_count;
			}
		}
	}
}

#endif //MATRIX_GENERATOR_H
