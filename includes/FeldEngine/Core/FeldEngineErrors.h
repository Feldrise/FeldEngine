#pragma once

#include <iostream>
#include <string>

namespace Fd
{
	inline void log(const char* msg, ostream& os = std::cerr) //TODO: Add type of msg
	{
		os << msg;
	}
	extern void fatalError(std::string const& errorString);
}
