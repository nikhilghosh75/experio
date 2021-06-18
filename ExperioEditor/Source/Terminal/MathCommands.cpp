#include "TerminalCommands.h"
#include "Runtime/Containers/LString.h"

int Math(const std::vector<std::string>& args)
{
	if (args.size() == 1)
	{
		return INVALID_ARG_COUNT;
	}

	float arg1 = LString::StringToFloat(args[1]);
	float arg2 = LString::StringToFloat(args[3]);

	float result;
	if (args[2] == "+")
		result = arg1 + arg2;
	else if (args[2] == "-")
		result = arg1 - arg2;
	else if (args[2] == "*")
		result = arg1 * arg2;
	else if (args[2] == "/")
		result = arg1 / arg2;

	Terminal::Print("The result is " + std::to_string(result));

	return 0;
}