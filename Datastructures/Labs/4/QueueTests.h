//
// Created by ed on 14.11.16.
//

#ifndef QUEUETESTS_QUEUE_H
#define QUEUETESTS_QUEUE_H

namespace QueueTests {
	template<class T, template<typename> class QUEUE>
	auto TestMemory(int size) -> decltype(sizeof(QUEUE<T>)) {
		QUEUE<T> queue;
		for (int i = 0; i < size; ++i) {
			queue.Enqueue(decltype(queue.Dequeue())());
		}
		return queue.get_memory_size();
	}
}

#endif //QUEUETESTS_QUEUE_H
