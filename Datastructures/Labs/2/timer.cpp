#include "timer.h"
#include <iostream>

Timer::Timer() {
	#ifdef WIN32
		QueryPerfomanceFrequency(&frequency);
		startCount.QuadPart = 0;
		endCount.QuadPart = 0;
	#else
		startCount.tv_sec = startCount.tv_usec = 0;
		endCount.tv_sec = endCount.tv_usec = 0;
	#endif

		startTimeInMicroSec = 0;
		endTimeInMicroSec = 0;
		stopped = false;
}

void Timer::start() {
	stopped = false;

	#ifdef WIN32
		QueryPerfomanceCounter(&startCount);
	#else
		gettimeofday(&startCount, nullptr);
	#endif
}

void Timer::stop() {
	stopped = true;

	#ifdef WIN32
		QueryPerfomanceCounter(&endCount);
	#else
		gettimeofday(&endCount, nullptr);
	#endif
}

double Timer::getElapsedTimeInMicroSec() {
	#ifdef WIN32
		if (!stopped){
			QueryPerfomanceCounter(&endCount);
		}

		startTimeInMicroSec = startCount.QuadPart * (1000000.0 / frequency.QuadPart);
		endTimeInMicrosec = endCount.QuadPart * (1000000.0 / frequency.QuadPart);
	#else
		if (!stopped){
			gettimeofday(&endCount, nullptr);
		}

		startTimeInMicroSec = (startCount.tv_sec * 1000000.0) + startCount.tv_usec;
		endTimeInMicroSec = (endCount.tv_sec * 1000000.0) + endCount.tv_usec;
	#endif

	return endTimeInMicroSec - startTimeInMicroSec;
}

double Timer::getElapsedTimeInMilliSec() {
	return this->getElapsedTimeInMicroSec() * 0.001;
}

double Timer::getElapsedTime() {
	return this->getElapsedTimeInMicroSec() * 0.000001;
}