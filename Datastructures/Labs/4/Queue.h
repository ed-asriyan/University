//
// Created by ed on 30.10.16.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include <exception>
#include <clocale>

template<class T>
class Queue {
	private:
		int size;

	public:
		class QueueEmptyException : public std::exception {};

		Queue();
		virtual ~Queue();

		void Enqueue(const T&);
		T Dequeue();

		const T& First() const;
		const T& Last() const;

		virtual void Clear();

		int get_size() const;

	protected:
		virtual void _enqueue(const T&) = 0;
		virtual T _dequeue() = 0;

		virtual const T& _first() const = 0;
		virtual const T& _last() const = 0;
};

template<class T>
Queue<T>::Queue() {
	size = 0;
}

template<class T>
Queue<T>::~Queue() {

}

template<class T>
int Queue<T>::get_size() const {
	return size;
}

template<class T>
void Queue<T>::Enqueue(const T& value) {
	_enqueue(value);
	++size;
}

template<class T>
T Queue<T>::Dequeue() {
	if (!size) {
		throw QueueEmptyException();
	}

	auto result = _dequeue();
	--size;
	return result;
}

template<class T>
const T& Queue<T>::First() const {
	if (!size) {
		throw QueueEmptyException();
	}
	return _first();
}

template<class T>
const T& Queue<T>::Last() const {
	if (!size) {
		throw QueueEmptyException();
	}
	return _last();
}

template<class T>
void Queue<T>::Clear() {
	while (size) {
		Dequeue();
	}
}

#endif //QUEUE_QUEUE_H
