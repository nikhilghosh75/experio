#include "TerminalCommands.h"
#include "Runtime/Core/SystemMetrics.h"
#include <sstream>

/*
example usage:
	resolution
*/

int Resolution(const std::vector<std::string>& args)
{
	if (args.size() > 1)
	{
		return INVALID_ARG_COUNT;
	}

	FResolution resolution = SystemMetrics::Resolution();

	std::stringstream ss;
	ss << "Width: " << resolution.width << " Height: " << resolution.height;
	Terminal::Print(ss.str());

	return 0;
}