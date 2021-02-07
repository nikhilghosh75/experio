#include "TerminalCommands.h"
#include "../Framework/Values.h"

/*
Example usage:
	add-layer Spaceship
*/

int AddLayer(const std::vector<std::string>& args)
{
	if (args.size() != 2)
	{
		return INVALID_ARG_COUNT;
	}

	if (ExperioEditor::NumValues(EValueType::Layer) >= 64)
	{
		Terminal::Print("There are too many layers already existing. Exiting program.");
		return 0;
	}

	ExperioEditor::AddValue(args[1], EValueType::Layer);
	Terminal::Print("Layer was added");

	return 0;
}