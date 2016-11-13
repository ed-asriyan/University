//
// Created by ed on 29.10.16.
//

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

#include "QueueArray.h"
#include "QueueList.h"
#include "ServiceUnit.h"
#include "RandomGenerator.h"

#define T1_MIN 0
#define T1_MAX 6

#define T2_MIN 1
#define T2_MAX 8

#define P 0.7

#define SU2_OUTCOME 1000

#define LOG_STEP 100

unsigned long long tick(void) {
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d));
	return d;
}

int main() {
	bool show_pointers;
	std::cout << "Print addresses of elements of QueueList? (0, 1): ";
	std::cin >> show_pointers;

	ServiceUnit<QueueArray> su1;
	ServiceUnit<QueueList> su2;

	su1.set_min_proc_time(T1_MIN);
	su1.set_max_proc_time(T1_MAX);

	su2.set_min_proc_time(T2_MIN);
	su2.set_max_proc_time(T2_MAX);

	auto tm = tick();

	for (int i = 0; i < SU2_OUTCOME; ++i) {
		su1.Enqueue(RequestUnit());
	}

	int last_su2_log_proc_time = -1;
	while (su2.get_proc_count() < SU2_OUTCOME) {
		if (su1.get_size()) {
			if (su1.get_curr_time() <= su2.get_curr_time()) {
				auto request = su1.Dequeue();
				if (RandomGenerator::GetRandomDouble01() > P) {
					su2.Enqueue(request);
				} else {
					su1.Enqueue(request);
				}
			}
		} else {
			su1.SynchronizeTime(su2);
		}

		su2.SynchronizeTime(su1);
		if (su2.get_size()) {
			if (su2.get_curr_time() <= su1.get_curr_time()) {
				auto request = su2.Dequeue();
				su1.Enqueue(request);
			}
		} else {
			su2.SynchronizeTime(su1);
		}

		if (!(su2.get_proc_count() % LOG_STEP) && su2.get_proc_count() != last_su2_log_proc_time) {
			if (show_pointers) {
				if (typeid(su1) == typeid(ServiceUnit<QueueList>)) {
					std::cout << "Addresses of SU1 elements: ";
					su1.ForEach([](const RequestUnit& elem) {
						std::cout << &elem << ' ';
					});
					std::cout << std::endl;
				}
				if (typeid(su2) == typeid(ServiceUnit<QueueList>)) {
					std::cout << "Addresses of SU2 elements: ";
					su2.ForEach([](const RequestUnit& elem) {
						std::cout << &elem << ' ';
					});
					std::cout << std::endl;
				}
			}

			std::cout << "SU2 processed " << (last_su2_log_proc_time = su2.get_proc_count()) << " requests"
			          << std::endl;
			std::cout << " Current SU1 queue length: " << su1.get_size() << std::endl;
			std::cout << " Current SU2 queue length: " << su2.get_size() << std::endl;
			std::cout << " Average SU1 queue length: " << su1.get_average_size() << std::endl;
			std::cout << " Average SU2 queue length: " << su2.get_average_size() << std::endl;
			std::cout << std::endl;
		}
	}

	std::cout << std::endl;

	tm = tick() - tm;

	std::cout << "--- Summary ---" << std::endl;
	std::cout << "SU1 is " << abi::__cxa_demangle(typeid(su1).name(), nullptr, nullptr, nullptr) << std::endl;
	std::cout << "SU2 is " << abi::__cxa_demangle(typeid(su2).name(), nullptr, nullptr, nullptr) << std::endl;
	std::cout << std::endl;

	std::cout << "SU1 processed " << su1.get_proc_count() << " requests" << std::endl;
	std::cout << "SU2 processed " << su2.get_proc_count() << " requests" << std::endl;
	std::cout << std::endl;

	std::cout << "SU1 average queue length: " << su1.get_average_size() << std::endl;
	std::cout << "SU2 average queue length: " << su2.get_average_size() << std::endl;
	std::cout << std::endl;

	std::cout << "SU1 average service time: " << su1.get_average_proc_time() << std::endl;
	std::cout << "SU2 average service time: " << su2.get_average_proc_time() << std::endl;
	std::cout << std::endl;

	std::cout << "SU1 average queueing time: " << su1.get_average_queueing_time() << std::endl;
	std::cout << "SU2 average queueing time: " << su2.get_average_queueing_time() << std::endl;
	std::cout << std::endl;

	std::cout << "SU1 idle time: " << su1.get_idle_time() << std::endl;
	std::cout << "SU2 idle time: " << su2.get_idle_time() << std::endl;
	std::cout << "Simulation time: " << std::max(su1.get_curr_time(), su2.get_curr_time()) << std::endl;
	std::cout << std::endl;

	const time_t su1_enqueue_time = su1.get_enqueue_time_sum();
	const time_t su1_dequeue_time = su1.get_dequeue_time_sum();
	const time_t su2_enqueue_time = su2.get_enqueue_time_sum();
	const time_t su2_dequeue_time = su2.get_dequeue_time_sum();
	std::cout << "SU1 CPU time: " << su1_enqueue_time + su1_dequeue_time << " (enqueue: " << su1_enqueue_time
	          << ", dequeue: " << su1_dequeue_time << ")" << std::endl;
	std::cout << "SU2 CPU time: " << su2_enqueue_time + su2_dequeue_time << " (enqueue: " << su2_enqueue_time
	          << ", dequeue: " << su2_dequeue_time << ")" << std::endl;
	std::cout << "Overal CPU time: " << tm << std::endl;

	return 0;
}