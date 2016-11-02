//
// Created by ed on 30.10.16.
//

#ifndef QUEUE_QUEUELIST_H
#define QUEUE_QUEUELIST_H

#include <cassert>

#include "Queue.h"

/**
 * Queue which is released on backward list rules
 */
template<class T>
class QueueList : public Queue<T> {
	private:
		struct Node {
			Node* prev;
			T value;

			Node(const T& value);
		};

		typedef Node* iterator;

		iterator tail;
		iterator head;
	public:
		QueueList();

		virtual void Clear() override;

	private:
		void init();

	protected:
		virtual void _enqueue(const T& t) override;
		virtual T _dequeue() override;

		virtual const T& _first() const override;
		virtual const T& _last() const override;

};

template<class T>
QueueList<T>::QueueList() {
	init();
}

template<class T>
void QueueList<T>::_enqueue(const T& t) {
	auto new_tail = new Node(t);

	// if queue is empty
	if (tail != nullptr) {
		assert(Queue<T>::get_size());
		tail->prev = new_tail;
	}

	tail = new_tail;
	if (head == nullptr) {
		head = tail;
	}
}

template<class T>
T QueueList<T>::_dequeue() {
	assert(Queue<T>::get_size());

	auto prev = head->prev;
	auto result = head->value;

	delete head;
	head = prev;

	// if queue contained only one item
	if (head == nullptr) {
		tail = nullptr;
	}

	return result;
}

template<class T>
void QueueList<T>::init() {
	tail = nullptr;
	head = nullptr;
}

template<class T>
void QueueList<T>::Clear() {
	Queue<T>::Clear();
	init();
}

template<class T>
const T& QueueList<T>::_first() const {
	assert(Queue<T>::get_size());
	return head->value;
}

template<class T>
const T& QueueList<T>::_last() const {
	assert(Queue<T>::get_size());
	return tail->value;
}

template<class T>
QueueList<T>::Node::Node(const T& value) : value(value) {}

#endif //QUEUE_QUEUELIST_H
