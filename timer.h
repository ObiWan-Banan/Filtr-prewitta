#pragma once
#include <Windows.h>
class Timer
{
	LARGE_INTEGER startingTime;
	LARGE_INTEGER endingTime;
	LARGE_INTEGER elapsedMicroseconds;
	LARGE_INTEGER frequency;

public:
	void start();

	void stop();

	int getTime();
};

