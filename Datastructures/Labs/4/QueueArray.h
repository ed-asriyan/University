//
// Created by ed on 30.10.16.
//

#ifndef QUEUE_QUEUEARRAY_H
#define QUEUE_QUEUEARRAY_H

#include <cassert>

#include "Queue.h"
#include "LoopedArray.h"

/**
 * Queue which is released on LoopedArray
 *
 * @see LoopedArray
 */
template<class T>
class QueueArray : public Queue<T> {
	private:
		typedef typename LoopedArray<T>::iterator iterator;

		const static int SIZE_FACTOR = 4;
		LoopedArray<T>* data;

		iterator front;
		iterator back;

	public:
		QueueArray();
		~QueueArray();

		virtual void Clear() override;
		
	private:
		void init();

		void reallocate();

	protected:
		virtual void _enqueue(const T&) override;
		virtual T _dequeue() override;
};

template<class T>
QueueArray<T>::QueueArray() {
	init();
}

template<class T>
QueueArray<T>::~QueueArray() {
	Queue<T>::Clear();
}

template<class T>
void QueueArray<T>::init() {
	data = nullptr;
}

template<class T>
void QueueArray<T>::Clear() {
	if (data != nullptr) {
		delete data;
	}
	init();
}

template<class T>
void QueueArray<T>::reallocate() {
	// new values
	int new_size = Queue<T>::get_size() * SIZE_FACTOR + 1;
	LoopedArray<T>* new_data = new LoopedArray<T>(new_size);
	iterator new_front = new_data->begin();
	iterator new_back = new_front;

	// if stack is not empty
	// copy items into new_data & delete old data
	if (data != NULL) {
		iterator it = front;
		do {
			*(new_back++) = *(it++);
		} while (it != back);

		delete data;
	}

	// accepting new values
	data = new_data;
	front = new_front;
	back = new_back;
}

template<class T>
void QueueArray<T>::_enqueue(const T& value) {
	// if stack is empty or buffer is full
	if (data == NULL || (Queue<T>::get_size() && front == back)) {
		reallocate();
	}

	*(--front) = value;
}

template<class T>
T QueueArray<T>::_dequeue() {
	assert(Queue<T>::get_size());

	return *(--back);
}

#endif //QUEUE_QUEUEARRAY_H
