//
// Created by lieroz on 14.12.16.
// Modified by ed on 19.12.16.
//

#ifndef LAB_07_HASHFUNC_H
#define LAB_07_HASHFUNC_H

#include <cstddef>
#include <random>

template<class K>
struct HashFunc {
	size_t operator()(const K& key, const size_t range) const {
		if (sizeof(K) < sizeof(unsigned int)) {
			const char* ptr = (const char*) &key;
			std::srand(static_cast<unsigned int>(*ptr));
		} else {
			const unsigned int* ptr = (const unsigned int*) &key;
			std::srand(*ptr);
		}
		return rand() % range;
	}
};

#endif //LAB_07_HASHFUNC_H
