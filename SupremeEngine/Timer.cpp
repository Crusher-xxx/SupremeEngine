#include "Timer.h"

Timer::Timer() : start{ std::chrono::high_resolution_clock::now() }
{
}

void Timer::reset()
{
	start = std::chrono::high_resolution_clock::now();
}

double Timer::get_passed_time()
{
	return std::chrono::duration_cast<std::chrono::microseconds>
		(std::chrono::high_resolution_clock::now() - start).count() / 1000.0;
}
