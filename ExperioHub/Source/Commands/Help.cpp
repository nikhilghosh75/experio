#include "../Core/HubCommands.h"
#include "../Core/HubApplication.h"

int Help(const std::vector<std::string>& args)
{
	std::cout << "Here are some acceptable commands:" << std::endl;
	const auto& functions = HubApplication::Get()->functions;
	functions.ForEach([](const std::string& str, const CommandFunction& function) {
		std::cout << "\t" << str << std::endl;
	});

	std::cout << "\t" << "quit" << std::endl;

	return 0;
}