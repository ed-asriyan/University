//
// Created by ed on 17.04.17.
//

#ifndef LAB2_BASEVECTOR_HPP
#define LAB2_BASEVECTOR_HPP

#include <cstddef>

class BaseVector {
	public:
		BaseVector() = default;
		BaseVector(const BaseVector&) = default;

		virtual ~BaseVector() = 0;

		size_t get_size() const;

	protected:
		size_t size = 0;
};

#endif //LAB2_BASEVECTOR_HPP
