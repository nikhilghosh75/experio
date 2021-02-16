#include "../Core/HubCommands.h"
#include "Runtime/Core/Core.h"

int Version(const std::vector<std::string>& args)
{
	std::cout << "Current Version: " << EXPERIO_BUILD_MAJOR << "."
		<< EXPERIO_BUILD_MINOR << "." << EXPERIO_BUILD_PATCH << std::endl;

	return 0;
}