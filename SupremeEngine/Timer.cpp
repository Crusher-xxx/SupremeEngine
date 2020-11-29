#include "Timer.h"
#include <string>

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

double Timer::get_delta_time() // Get passed time in seconds with high precision
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>
		(std::chrono::high_resolution_clock::now() - start).count() / 1000000000.0;
}

std::string Timer::get_fps()
{
	static double since_last_update{ 0 };
	if (since_last_update > 100)
	{
		since_last_update = 0;
		return std::to_string(static_cast<int>(1000 / get_passed_time()));
	}
	else
	{
		since_last_update += get_passed_time();
		return "";
	}
}
