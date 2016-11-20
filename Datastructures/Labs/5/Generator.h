//
// Created by ed on 20.11.16.
//

#ifndef MATRIX_GENERATOR_H
#define MATRIX_GENERATOR_H

namespace Generator {
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
}

#endif //MATRIX_GENERATOR_H
