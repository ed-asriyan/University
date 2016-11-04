//
// Created by ed on 29.10.16.
//

#include <iostream>

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
	ServiceUnit<QueueArray> su1;
	ServiceUnit<QueueList> su2;

	double su2_idle_time = 0;
	double su2_remaining_service_time = 0;

	su1.set_min_proc_time(T1_MIN);
	su1.set_max_proc_time(T1_MAX);

	su2.set_min_proc_time(T2_MIN);
	su2.set_max_proc_time(T2_MAX);

	auto tm = tick();

	for (int i = 0; i < SU2_OUTCOME; ++i) {
		su1.Enqueue(RequestUnit());
	}

	for (int i = 0; i < SU2_OUTCOME;) {
		if (su1.get_size()) {
			auto request = su1.Dequeue();

			su2_remaining_service_time -= request.service_time;

			request.Reset();

			if (RandomGenerator::GetRandomDouble01() > P) {
				su2.Enqueue(request);
			} else {
				su1.Enqueue(request);
			}
		}

		if (su2_remaining_service_time <= 0 || !su1.get_size()) {
			if (su2.get_size()) {
				su2_remaining_service_time += su2.Dequeue().service_time;
				++i;
			} else {
				su2_idle_time += -su2_remaining_service_time;
				su2_remaining_service_time = 0;
			}
		}

		if (!(i % LOG_STEP)) {
			std::cout << "SU2 processed " << su2.get_proc_count() << " requests" << std::endl;
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

	std::cout << "SU1 processed " << su1.get_proc_count() << " requests" << std::endl;
	std::cout << "SU2 processed " << su2.get_proc_count() << " requests" << std::endl;
	std::cout << std::endl;

	std::cout << "SU1 average service time: " << su1.get_average_proc_time() << std::endl;
	std::cout << "SU2 average service time: " << su2.get_average_proc_time() << std::endl;
	std::cout << std::endl;

	std::cout << "SU1 average queueing time: " << su1.get_average_queueing_time() << std::endl;
	std::cout << "SU2 average queueing time: " << su2.get_average_queueing_time() << std::endl;
	std::cout << std::endl;

	std::cout << "SU2 idle time: " << su2_idle_time << std::endl;
	std::cout << "Simulation time: " << su2.get_sum_proc_time() << std::endl;
	std::cout << "CPU time: " << tm << std::endl;

	return 0;
}