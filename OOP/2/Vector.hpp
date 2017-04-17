//
// Created by ed on 18.04.17.
//

#ifndef LAB2_VECTOR_HPP
#define LAB2_VECTOR_HPP

#include <ostream>
#include <initializer_list>

#include "BaseVector.hpp"
#include "Iterator.hpp"

template<class T>
class Vector : public BaseVector {
	public:
		Vector(const Vector& vector);
		Vector(Vector&& vector);
		Vector(size_t _size);
		Vector(const std::initializer_list<T>& initializer_list);

		virtual ~Vector();

		Iterator<T> begin();
		Iterator<T> begin() const;
		Iterator<T> end();
		Iterator<T> end() const;

		template<class T1>
		friend std::ostream& operator<<(std::ostream& out, const Vector<T1>& b);

	private:
		T* data;
};

template<class T>
Vector<T>::Vector(size_t _size) {
	data = new T[_size];
	size = _size;
}

template<class T>
Vector<T>::Vector(const Vector& vector)
	: Vector(vector.size) {
	std::copy(vector.begin(), vector.end(), begin());
}

template<class T>
Vector<T>::Vector(Vector&& vector) {
	data = vector.data;
	size = vector.size;
	vector.data = nullptr;
	vector.size = 0;
}

template<class T>
Vector<T>::Vector(const std::initializer_list<T>& initializer_list)
	: Vector(initializer_list.size()) {
	std::copy(initializer_list.begin(), initializer_list.end(), begin());
}

template<class T>
Vector<T>::~Vector() {
	delete[] data;
}

template<class T>
Iterator<T> Vector<T>::begin() {
	return Iterator<T>(data);
}

template<class T>
Iterator<T> Vector<T>::begin() const {
	return Iterator<const T>(data);
}

template<class T>
Iterator<T> Vector<T>::end() {
	return Iterator<T>(data + size);
}

template<class T>
Iterator<T> Vector<T>::end() const {
	return Iterator<const T>(data + size);
}

template<class T1>
std::ostream& operator<<(std::ostream& out, const Vector<T1>& b) {
	for (size_t i = 0; i < b.size; ++i) {
		out << b.data[i] << ' ';
	}
	return out;
}

#endif //LAB2_VECTOR_HPP
