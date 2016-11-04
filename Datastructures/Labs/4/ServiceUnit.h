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
#include "RandomGenerator.h"

template<template<typename> class QUEUE>
class ServiceUnit {
	private:
		QUEUE<RequestUnit> income1;
		QUEUE<RequestUnit> income2;
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

		void Process();

		QUEUE<RequestUnit>& Income1();
		QUEUE<RequestUnit>& Income2();
		QUEUE<RequestUnit>& Outcome();
		double get_curr_time() const;
		double get_min_proc_time() const;
		double get_max_proc_time() const;
		double get_idle_time() const;
		double get_sum_proc_time() const;
		double get_sum_queuing_time() const;
		int get_proc_count() const;
		int get_sum_queue_length() const;

		void set_min_proc_time(double min_proc_time);
		void set_max_proc_time(double max_proc_time);

};

template<template<typename> class QUEUE>
ServiceUnit<QUEUE>::ServiceUnit() {
	// check for Queue class
	assert((std::is_base_of<Queue<RequestUnit>, QUEUE<RequestUnit>>::value));
}

template<template<typename> class QUEUE>
QUEUE<RequestUnit>& ServiceUnit<QUEUE>::Income1() {
	return income1;
}

template<template<typename> class QUEUE>
QUEUE<RequestUnit>& ServiceUnit<QUEUE>::Income2() {
	return income2;
}

template<template<typename> class QUEUE>
QUEUE<RequestUnit>& ServiceUnit<QUEUE>::Outcome() {
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

template<template<typename> class QUEUE>
void ServiceUnit<QUEUE>::Process() {
	RequestUnit r1, r2, r_tmp;
	int r1_len = income1.get_size();
	int r2_len = income2.get_size();

	sum_queue_length += r1_len + r2_len;

	if (r1_len || r2_len) {
		if (r1_len && r2_len) {
			if (r1.income_time < r2.income_time) {
				r_tmp = income1.Dequeue();
			} else {
				r_tmp = income2.Dequeue();
				r1 = r2;
			}
		} else {
			if (r1_len) {
				r_tmp = income1.Dequeue();
			} else {
				r_tmp = income2.Dequeue();
				r1 = r2;
			}
		}
	}

	double proc_time = min_proc_time + (max_proc_time - min_proc_time) * RandomGenerator::GetRandomDouble01();

	if (curr_time > r1.income_time) {
		r1.querring_time = curr_time - r1.income_time;
	} else {
		idle_time += r1.income_time - curr_time;
		curr_time = r1.income_time;

		r1.querring_time = 0;
	}

	curr_time += proc_time;
	sum_queuing_time += r1.querring_time;
	sum_proc_time += proc_time;

	r1.outcome_time = curr_time;
	r1.querring_time = r1.outcome_time;
	++r1.proc_count;

	++proc_count;
	outcome.Enqueue(r1);

}

template<template<typename> class QUEUE>
void ServiceUnit<QUEUE>::set_min_proc_time(double min_proc_time) {
	ServiceUnit<QUEUE>::min_proc_time = min_proc_time;
}

template<template<typename> class QUEUE>
void ServiceUnit<QUEUE>::set_max_proc_time(double max_proc_time) {
	ServiceUnit<QUEUE>::max_proc_time = max_proc_time;
}

#endif //QUEUE_SERVICEUNIT_H
