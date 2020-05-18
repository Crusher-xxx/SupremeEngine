#pragma once
#include<chrono>

class Timer
{
public:
	Timer();
	void reset();
	double get_passed_time();
private:
	std::chrono::steady_clock::time_point start;
};