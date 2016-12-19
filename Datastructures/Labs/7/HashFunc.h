//
// Created by lieroz on 14.12.16.
//

#ifndef LAB_07_HASHFUNC_H
#define LAB_07_HASHFUNC_H

#include <cstddef>

template<class K>
struct HashFunc {
	size_t operator()(const K& key, const size_t range) const {
		return (key) % range;
	}
};

#endif //LAB_07_HASHFUNC_H
