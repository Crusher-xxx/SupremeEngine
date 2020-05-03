#include "Logger.h"
#include <string>
#include <iostream>


void print_log_message(std::string message, unsigned int newlines)
{
	std::clog << "_____________________________________________________________________" << message;
	for (size_t i = 0; i < newlines; i++)
	{
		std::clog << '\n';
	}
}