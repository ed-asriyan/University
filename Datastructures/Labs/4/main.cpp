#include <iostream>

#include "QueueArray.h"
#include "QueueList.h"
#include "ServiceUnit.h"
#include "RandomGenerator.h"

#define T1_MIN 0
#define T1_MAX 6

#define T2_MIN 1
#define T2_MAX 8

#define P 0.5

#define SU1_INCOME 100
#define SU2_OUTCOME 1000

#define EXPECTED_TIME (double)(T1_MAX + T1_MIN) / 2 / (1 - P) * SU2_OUTCOME

#define LOG_STEP 100

unsigned long long tick(void) {
	unsigned long long d;
	__asm__ __volatile__ ("rdtsc" : "=A" (d));
	return d;
}

int main() {
	ServiceUnit<QueueArray> su1, su2;

	su1.set_min_proc_time(T1_MIN);
	su1.set_max_proc_time(T1_MAX);

	su2.set_min_proc_time(T2_MIN);
	su2.set_max_proc_time(T2_MAX);

	auto tm = tick();

	for (int i = 0; i < SU1_INCOME; ++i) {
		su1.Income1().Enqueue(RequestUnit(i));
	}

	while (su2.get_proc_count() < SU2_OUTCOME) {
		RequestUnit r1, r2;

		su1.Process();

		if (su1.Outcome().get_size()) {
			r1 = su1.Outcome().Dequeue();
			double rnd = RandomGenerator::GetRandomDouble01();
			if (rnd > P) {
				su2.Income1().Enqueue(r1);
			} else {
				su1.Income1().Enqueue(r1);
			}
		}

		su2.Process();

		if (su2.Outcome().get_size()) {
			r2 = su2.Outcome().Dequeue();
			su1.Income1().Enqueue(r2);

			if (su2.get_proc_count() % LOG_STEP == 0) {
				std::cout << "SU2 processed " << su2.get_proc_count() << " requests" << std::endl;
				std::cout << " Current SU1 queue length: " << su1.Income1().get_size() + su1.Income2().get_size()
				          << std::endl;
				std::cout << " Average SU1 queue length: " << (double) su1.get_sum_queue_length() / su1.get_proc_count()
				          << std::endl;
				std::cout << " Current SU2 queue length: " << su2.Income1().get_size() + su2.Income2().get_size()
				          << std::endl;
				std::cout << " Average SU2 queue length: " << (double) su2.get_sum_queue_length() / su2.get_proc_count()
				          << std::endl;
				std::cout << std::endl;
			}
		}
	}
	std::cout << std::endl;

	tm = tick() - tm;

	std::cout << "Summary:" << std::endl;
	std::cout << " Simulation time: " << su2.get_curr_time() << " (expected " << EXPECTED_TIME << ") [divergence: "
	          << (su2.get_curr_time() - EXPECTED_TIME) / 100 << "]" << std::endl;

	std::cout << " SU2 idle time: " << su2.get_idle_time() << std::endl;
	std::cout << " SU1 processed " << su1.get_proc_count() << " requests" << std::endl;
	std::cout << " Average queueing time: " << su1.get_sum_queuing_time() / su1.get_proc_count() << std::endl;
	std::cout << "  CPU time: " << tm << std::endl;

	return 0;
}