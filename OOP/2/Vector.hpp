//
// Created by ed on 18.04.17.
//

#ifndef LAB2_VECTOR_HPP
#define LAB2_VECTOR_HPP

#include <ostream>
#include <iomanip>
#include <initializer_list>

#include "BaseVector.hpp"
#include "Iterator.hpp"
#include "Errors.hpp"

template<class T>
class Vector : public BaseVector {
	public:
		Vector(const Vector& vector);
		Vector(Vector&& vector);
		Vector(size_t _size);
		Vector(const std::initializer_list<T>& initializer_list);

		virtual ~Vector();

		Vector<T>& operator=(const Vector<T>& b);
		Vector<T>& operator=(const std::initializer_list<T>& b);
		Vector<T>& operator=(Vector<T>&& b);

		Vector<T>& minus();
		Vector<T>& add(const Vector<T>& b);
		Vector<T>& subtract(const Vector<T>& b);
		Vector<T>& divide(const T& b);
		Vector<T>& multiply(const T& b);
		T multiply(const Vector<T>& b) const;
		bool isOrtogonal(const Vector<T>& b) const;
		bool equals(const Vector<T>& b) const;

		Vector<T> operator-() const;

		Vector<T>& operator+=(const Vector<T>& b);
		Vector<T> operator+(const Vector<T>& b) const;

		Vector<T>& operator-=(const Vector<T>& b);
		Vector<T> operator-(const Vector<T>& b) const;

		Vector<T>& operator*=(const T& b);
		Vector<T> operator*(const T& b) const;
		T operator*(const Vector<T>& b) const;

		Vector<T>& operator/=(const T& b);
		Vector<T> operator/(const T& b) const;

		T& operator[](size_t i);
		const T& operator[](size_t i) const;

		bool operator==(const Vector<T>& b) const;
		bool operator!=(const Vector<T>& b) const;

		bool operator&&(const Vector<T>& b) const;

		Iterator<T> begin();
		Iterator<const T> begin() const;
		Iterator<T> end();
		Iterator<const T> end() const;

		template<class T1>
		friend std::ostream& operator<<(std::ostream& out, const Vector<T1>& b);

		template<class T1>
		friend Vector<T1> operator+(const T1& a, const Vector<T1>& b);

		template<class T1>
		friend Vector<T1> operator*(const T1& a, const Vector<T1>& b);

	private:
		void resize(size_t new_size);

		T* data = nullptr;
};

template<class T>
Vector<T>::Vector(size_t _size) {
	resize(_size);
}

template<class T>
Vector<T>::Vector(const Vector& vector) {
	*this = vector;
}

template<class T>
Vector<T>::Vector(Vector&& vector) {
	*this = vector;
}

template<class T>
Vector<T>::Vector(const std::initializer_list<T>& initializer_list) {
	*this = initializer_list;
}

template<class T>
Vector<T>::~Vector() {
	resize(0);
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& b) {
	resize(b.size);
	std::copy(b.begin(), b.end(), begin());
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& b) {
	data = b.data;
	size = b.size;
	b.data = nullptr;
	b.size = 0;
	return *this;
}

template<class T>
Vector<T>& Vector<T>::operator=(const std::initializer_list<T>& b) {
	resize(b.size());
	std::copy(b.begin(), b.end(), begin());
}

template<class T>
T& Vector<T>::operator[](size_t i) {
	if (i >= size) throw IndexOutOfRangeException();
	return data[i];
}

template<class T>
const T& Vector<T>::operator[](size_t i) const {
	if (i >= size) throw IndexOutOfRangeException();
	return data[i];
}

template<class T>
bool Vector<T>::operator==(const Vector<T>& b) const {
	return equals(b);
}

template<class T>
bool Vector<T>::operator!=(const Vector<T>& b) const {
	return !equals(b);
}

template<class T>
Iterator<T> Vector<T>::begin() {
	return Iterator<T>(data);
}

template<class T>
Iterator<const T> Vector<T>::begin() const {
	return Iterator<const T>(data);
}

template<class T>
Iterator<T> Vector<T>::end() {
	return Iterator<T>(data + size);
}

template<class T>
Iterator<const T> Vector<T>::end() const {
	return Iterator<const T>(data + size);
}

template<class T>
void Vector<T>::resize(size_t new_size) {
	delete[] data;
	data = new_size ? new T[new_size] : nullptr;
	size = new_size;
}

template<class T>
Vector<T>& Vector<T>::minus() {
	for (auto& a: *this) {
		a = -a;
	}
	return *this;
}

template<class T>
Vector<T>& Vector<T>::add(const Vector<T>& b) {
	if (size != b.size) throw InvalidSizeException();
	for (size_t i = 0; i < size; ++i) {
		data[i] += b.data[i];
	}
	return *this;
}

template<class T>
Vector<T>& Vector<T>::subtract(const Vector<T>& b) {
	if (size != b.size) throw InvalidSizeException();
	for (size_t i = 0; i < size; ++i) {
		data[i] -= b.data[i];
	}
	return *this;
}

template<class T>
Vector<T>& Vector<T>::divide(const T& b) {
	if (!b) throw DivisionByZeroException();
	for (auto& a: *this) {
		a /= b;
	}
	return *this;
}

template<class T>
Vector<T>& Vector<T>::multiply(const T& b) {
	for (auto& a: *this) {
		a *= b;
	}
	return *this;
}

template<class T>
T Vector<T>::multiply(const Vector<T>& b) const {
	if (size != b.size) throw InvalidSizeException();
	T result = 0;
	for (size_t i = 0; i < size; ++i) {
		result += data[i] + b.data[i];
	}
	return result;
}

template<class T>
bool Vector<T>::isOrtogonal(const Vector<T>& b) const {
	return !(*this * b);
}

template<class T>
bool Vector<T>::equals(const Vector<T>& b) const {
	return std::equal(begin(), end(), b.begin(), b.end());
}

template<class T>
Vector<T> Vector<T>::operator-() const {
	auto result = *this;
	result.minus();
	return result;
}

template<class T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& b) {
	return add(b);
}

template<class T>
Vector<T> Vector<T>::operator+(const Vector<T>& b) const {
	auto result = *this;
	result.add(b);
	return result;
}

template<class T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& b) {
	return subtract(b);
}

template<class T>
Vector<T> Vector<T>::operator-(const Vector<T>& b) const {
	auto result = *this;
	result.subtract(b);
	return result;
}

template<class T>
Vector<T>& Vector<T>::operator*=(const T& b) {
	return multiply(b);
}

template<class T>
Vector<T> Vector<T>::operator*(const T& b) const {
	auto result = *this;
	result.multiply(b);
	return result;
}

template<class T>
T Vector<T>::operator*(const Vector<T>& b) const {
	return multiply(b);
}

template<class T>
Vector<T>& Vector<T>::operator/=(const T& b) {
	return divide(b);
}

template<class T>
Vector<T> Vector<T>::operator/(const T& b) const {
	auto result = *this;
	result.divide(b);
	return result;
}

template<class T>
bool Vector<T>::operator&&(const Vector<T>& b) const {
	return isOrtogonal(b);
}

template<class T1>
std::ostream& operator<<(std::ostream& out, const Vector<T1>& b) {
	for (auto& a: b) {
		out << std::setw(6) << a << ' ';
	}
	return out;
}

template<class T1>
Vector<T1> operator+(const T1& a, const Vector<T1>& b) {
	return b + a;
}

template<class T1>
Vector<T1> operator*(const T1& a, const Vector<T1>& b) {
	return b * a;
}

#endif //LAB2_VECTOR_HPP
