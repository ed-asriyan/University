#ifndef TIMER_H_DEF
#define TIMER_H_DEF

#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

class Timer {
	private:
		double startTimeInMicroSec;
		double endTimeInMicroSec;
		bool stopped;

	#ifdef WIN32
		LARGE_INTEGER frequency;
		LARGE_INTEGER startCount;
		LARGE_INTEGER endCount;
	#else
		timeval startCount;
		timeval endCount;
	#endif

	public:
		Timer();
		~Timer() {}

		void start();
		void stop();
		double getElapsedTime();
		double getElapsedTimeInMilliSec();
		double getElapsedTimeInMicroSec();
};

#endif // TIMER_H_DEF