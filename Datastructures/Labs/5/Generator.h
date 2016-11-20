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
		std::uniform_int_distribution<int> row_distr(0, height - 1);
		std::uniform_int_distribution<int> col_distr(0, width - 1);

		T default_item;
		while (items_count) {
			int row = row_distr(rd);
			int col = col_distr(rd);

			auto item = matrix.get_item(row, col);
			T value = distr(rd);

			if (item == default_item) {
				matrix.set_item(row, col, value);
				--items_count;
			}
		}
	}

	/**
	 * @brief Generates random double in range from min to max.
	 * @param min Lower border.
	 * @param max Highter border.
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
