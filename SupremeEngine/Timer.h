#pragma once
#include<chrono>
#include<string>

class Timer
{
public:
	Timer();
	void reset();
	double get_passed_time();
	double get_delta_time();
	std::string get_fps();
private:
	std::chrono::steady_clock::time_point start;
};