//
// Created by ed on 31.10.16.
//

#ifndef QUEUE_SERVICEUNIT_H
#define QUEUE_SERVICEUNIT_H

#include <cassert>
#include <exception>
#include <type_traits>

#include "Queue.h"
#include "RequestUnit.h"
#include "QueueArray.h"

template<template<typename> class QUEUE>
class ServiceUnit {
	private:
		QUEUE<RequestUnit> income;
		QUEUE<RequestUnit> outcome;

		double curr_time = 0;
		double min_proc_time = 0;
		double max_proc_time = 0;
		double idle_time = 0;
		double sum_proc_time = 0;
		double sum_queuing_time = 0;

		int proc_count = 0;
		int sum_queue_length = 0;

	public:
		class NotSupportedQueueTypeException : public std::exception {};

		ServiceUnit();

		const QUEUE<RequestUnit>& get_income() const;
		const QUEUE<RequestUnit>& get_outcome() const;
		double get_curr_time() const;
		double get_min_proc_time() const;
		double get_max_proc_time() const;
		double get_idle_time() const;
		double get_sum_proc_time() const;
		double get_sum_queuing_time() const;
		int get_proc_count() const;
		int get_sum_queue_length() const;

};

template<template<typename> class QUEUE>
ServiceUnit<QUEUE>::ServiceUnit() {
	// check for Queue class
	assert((std::is_base_of<QUEUE<RequestUnit>, QueueArray<RequestUnit>>::value));
}

template<template<typename> class QUEUE>
const QUEUE<RequestUnit>& ServiceUnit<QUEUE>::get_income() const {
	return income;
}

template<template<typename> class QUEUE>
const QUEUE<RequestUnit>& ServiceUnit<QUEUE>::get_outcome() const {
	return outcome;
}

template<template<typename> class QUEUE>
double ServiceUnit<QUEUE>::get_curr_time() const {
	return curr_time;
}

template<template<typename> class QUEUE>
double ServiceUnit<QUEUE>::get_min_proc_time() const {
	return min_proc_time;
}

template<template<typename> class QUEUE>
double ServiceUnit<QUEUE>::get_max_proc_time() const {
	return max_proc_time;
}

template<template<typename> class QUEUE>
double ServiceUnit<QUEUE>::get_idle_time() const {
	return idle_time;
}

template<template<typename> class QUEUE>
double ServiceUnit<QUEUE>::get_sum_proc_time() const {
	return sum_proc_time;
}

template<template<typename> class QUEUE>
double ServiceUnit<QUEUE>::get_sum_queuing_time() const {
	return sum_queuing_time;
}

template<template<typename> class QUEUE>
int ServiceUnit<QUEUE>::get_proc_count() const {
	return proc_count;
}

template<template<typename> class QUEUE>
int ServiceUnit<QUEUE>::get_sum_queue_length() const {
	return sum_queue_length;
}

#endif //QUEUE_SERVICEUNIT_H
