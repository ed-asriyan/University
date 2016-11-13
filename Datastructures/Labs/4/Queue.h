//
// Created by ed on 30.10.16.
//

#ifndef QUEUE_QUEUE_H
#define QUEUE_QUEUE_H

#include <exception>
#include <clocale>
#include <functional>
#include <ctime>

template<class T>
class Queue {
	private:
		int size = 0;

		time_t enqueue_time_sum = 0;
		time_t dequeue_time_sum = 0;

		int enqueue_count = 0;
		int dequeue_count = 0;
	public:
		class QueueEmptyException : public std::exception {};

		Queue() = default;
		virtual ~Queue() = default;

		void Enqueue(const T&);
		T Dequeue();

		const T& First() const;
		const T& Last() const;

		virtual void Clear();

		virtual void ForEach(const std::function<void(T&)>&) = 0;
		virtual void ForEach(const std::function<void(const T&)>&) const = 0;

		int get_size() const;

		time_t get_enqueue_time_sum() const;
		time_t get_dequeue_time_sum() const;
		int get_enqueue_count() const;
		int get_dequeue_count() const;

	protected:
		virtual void _enqueue(const T&) = 0;
		virtual T _dequeue() = 0;

		virtual const T& _first() const = 0;
		virtual const T& _last() const = 0;
};

template<class T>
int Queue<T>::get_size() const {
	return size;
}

template<class T>
void Queue<T>::Enqueue(const T& value) {
	auto time = std::clock();
	_enqueue(value);
	enqueue_time_sum += std::clock() - time;
	++enqueue_count;
	++size;
}

template<class T>
T Queue<T>::Dequeue() {
	if (!size) {
		throw QueueEmptyException();
	}

	auto time = std::clock();
	auto result = _dequeue();
	dequeue_time_sum += std::clock() - time;
	--dequeue_count;
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

template<class T>
time_t Queue<T>::get_enqueue_time_sum() const {
	return enqueue_time_sum;
}

template<class T>
time_t Queue<T>::get_dequeue_time_sum() const {
	return dequeue_time_sum;
}

template<class T>
int Queue<T>::get_enqueue_count() const {
	return enqueue_count;
}

template<class T>
int Queue<T>::get_dequeue_count() const {
	return dequeue_count;
}

#endif //QUEUE_QUEUE_H
