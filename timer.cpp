#include "timer.h"

void Timer::start()
{
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&startingTime);
}

void Timer::stop()
{
	QueryPerformanceCounter(&endingTime);
	elapsedMicroseconds.QuadPart = endingTime.QuadPart - startingTime.QuadPart;
	elapsedMicroseconds.QuadPart *= 1000000; // to avoid loss-of-precision converting to microseconds before dividing by tick-per-secod
	elapsedMicroseconds.QuadPart /= frequency.QuadPart;
	elapsedMicroseconds.QuadPart /= 1000; // convert to ms
}

int Timer::getTime()
{
	return (int)elapsedMicroseconds.QuadPart;
}
