//
// Created by ed on 18.04.17.
//

#ifndef LAB2_ITERATOR_HPP
#define LAB2_ITERATOR_HPP

#include <cstddef>

template<class T>
class Iterator {
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef size_t difference_type;
		typedef T* pointer;
		typedef T& reference;
		typedef const T* const_pointer;
		typedef const T& const_reference;

		Iterator(T* init);
		Iterator(const Iterator<T>& Right);

		reference operator*();
		const_reference operator*() const;
		pointer operator->();
		const_pointer operator->() const;

		Iterator<T>& operator=(const Iterator<T>& Right);
		Iterator<T>& operator=(T* Init);

		Iterator<T> operator+=(size_t n);
		Iterator<T> operator+(size_t n) const;
		Iterator<T> operator++(int);
		Iterator<T>& operator++();

		Iterator<T> operator-=(size_t n);
		Iterator<T> operator-(size_t n) const;
		Iterator<T> operator--(int);
		Iterator<T>& operator--();

		difference_type operator-(const Iterator<T>& b) const;

		bool operator<=(const Iterator<T>& b) const;
		bool operator<(const Iterator<T>& b) const;
		bool operator>=(const Iterator<T>& b) const;
		bool operator>(const Iterator<T>& b) const;
		bool operator==(const Iterator<T>& b) const;
		bool operator!=(const Iterator<T>& b) const;

	private:
		T* ptr;
};

template<class T>
Iterator<T>::Iterator(T* init)
	: ptr(init) {

}

template<class T>
Iterator<T>::Iterator(const Iterator<T>& Right)
	: Iterator(Right.ptr) {

}

template<class T>
typename Iterator<T>::reference Iterator<T>::operator*() {
	return *ptr;
}

template<class T>
typename Iterator<T>::const_reference Iterator<T>::operator*() const {
	return *ptr;
}

template<class T>
typename Iterator<T>::pointer Iterator<T>::operator->() {
	return ptr;
}

template<class T>
typename Iterator<T>::const_pointer Iterator<T>::operator->() const {
	return ptr;
}

template<class T>
Iterator<T>& Iterator<T>::operator=(T* b) {
	ptr = b;
	return *this;
}

template<class T>
Iterator<T>& Iterator<T>::operator=(const Iterator<T>& b) {
	ptr = b.ptr;
	return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator+=(size_t n) {
	ptr += n;
	return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator+(size_t n) const {
	auto result = *this;
	result += n;
	return result;
}

template<class T>
Iterator<T> Iterator<T>::operator++(int) {
	auto result = *this;
	++result;
	return result;
}

template<class T>
Iterator<T>& Iterator<T>::operator++() {
	++ptr;
	return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator-=(size_t n) {
	ptr -= n;
	return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator-(size_t n) const {
	auto result = *this;
	result -= n;
	return *this;
}

template<class T>
Iterator<T> Iterator<T>::operator--(int) {
	Iterator<T> it(*this);
	ptr++;
	return it;
}

template<class T>
Iterator<T>& Iterator<T>::operator--() {
	--ptr;
	return *this;
}

template<class T>
bool Iterator<T>::operator<=(const Iterator<T>& b) const {
	return ptr <= b.ptr;
}

template<class T>
bool Iterator<T>::operator<(const Iterator<T>& b) const {
	return ptr < b.ptr;
}

template<class T>
bool Iterator<T>::operator>=(const Iterator<T>& b) const {
	return ptr >= b.ptr;
}

template<class T>
bool Iterator<T>::operator>(const Iterator<T>& b) const {
	return ptr > b.ptr;
}

template<class T>
bool Iterator<T>::operator==(const Iterator<T>& b) const {
	return ptr == b.ptr;
}

template<class T>
bool Iterator<T>::operator!=(const Iterator<T>& b) const {
	return ptr != b.ptr;
}

template<class T>
typename Iterator<T>::difference_type Iterator<T>::operator-(const Iterator<T>& b) const {
	return ptr - b.ptr;
}

#endif //LAB2_ITERATOR_HPP
