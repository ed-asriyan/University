//
// Created by ed on 29.10.16.
//

#ifndef QUEUE_LOOPEDARRAY_H
#define QUEUE_LOOPEDARRAY_H

/**
 * A looped array
 *
 * begin - 1 == end - 1
 * (end - 1) + 1 == begin
 */
template<class T>
class LoopedArray {
	private:
		T* data_begin;
		T* data_end;

		int size;
	public:
		class iterator {
			private:
				LoopedArray* parent;
				T* ptr;

			public:
				iterator();
				iterator(LoopedArray* parent_, T* ptr_);

				T& operator*();
				const T& operator*() const;

				iterator operator++(int);
				iterator& operator++();
				iterator operator--(int);
				iterator& operator--();

				bool operator==(const iterator& it) const;
				bool operator!=(const iterator& it) const;

				friend iterator LoopedArray<T>::begin();
				friend iterator LoopedArray<T>::end();
		};

		typedef const iterator const_iterator;

		LoopedArray(int size_);
		~LoopedArray();

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;

		int get_size() const;
};

template<class T>
LoopedArray<T>::LoopedArray(int size_) {
	data_begin = new T[size = size_];
	data_end = data_begin + size;
}

template<class T>
LoopedArray<T>::~LoopedArray() {
	delete[] data_begin;
}

template<class T>
typename LoopedArray<T>::iterator LoopedArray<T>::begin() {
	return iterator(this, data_begin);
}

template<class T>
typename LoopedArray<T>::const_iterator LoopedArray<T>::begin() const {
	return iterator(this, data_begin);
}

template<class T>
typename LoopedArray<T>::iterator LoopedArray<T>::end() {
	return iterator(this, data_end);
}

template<class T>
typename LoopedArray<T>::const_iterator LoopedArray<T>::end() const {
	return iterator(this, data_end - 1);
}

template<class T>
int LoopedArray<T>::get_size() const {
	return size;
}

template<class T>
LoopedArray<T>::iterator::iterator() {

}

template<class T>
LoopedArray<T>::iterator::iterator(LoopedArray* parent_, T* ptr_) {
	parent = parent_;
	ptr = ptr_;
}

template<class T>
T& LoopedArray<T>::iterator::operator*() {
	return *ptr;
}

template<class T>
const T& LoopedArray<T>::iterator::operator*() const {
	return *ptr;
}

template<class T>
typename LoopedArray<T>::iterator LoopedArray<T>::iterator::operator++(int) {
	iterator result(*this);
	operator++();
	return result;
}

template<class T>
typename LoopedArray<T>::iterator& LoopedArray<T>::iterator::operator++() {
	T* next = ptr + 1;
	if (next == parent->data_end) {
		next = parent->data_begin;
	}
	this->ptr = next;

	return *this;
}

template<class T>
typename LoopedArray<T>::iterator LoopedArray<T>::iterator::operator--(int) {
	iterator result(*this);
	operator--();
	return result;
}

template<class T>
typename LoopedArray<T>::iterator& LoopedArray<T>::iterator::operator--() {
	T* prev = ptr - 1;
	if (prev == parent->data_begin - 1) {
		prev = parent->data_end - 1;
	}
	this->ptr = prev;
	return *this;
}

template<class T>
bool LoopedArray<T>::iterator::operator==(const LoopedArray<T>::iterator& it) const {
	return ptr == it.ptr;
}

template<class T>
bool LoopedArray<T>::iterator::operator!=(const LoopedArray<T>::iterator& it) const {
	return ptr != it.ptr;
}

#endif //QUEUE_LOOPEDARRAY_H
