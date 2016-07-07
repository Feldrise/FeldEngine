#pragma once

#include <iostream>
#include <string>

namespace Fd
{
	inline void log(const std::string& msg, ostream& os = std::cerr) //TODO: Add type of msg
	{
		os << msg << std::flush;
	}
	extern void fatalError(std::string const& errorString);
}
