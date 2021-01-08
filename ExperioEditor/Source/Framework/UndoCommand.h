#pragma once
#include <string>

class UndoCommand
{
public:
	std::string name;

	virtual void Execute() = 0;
	virtual void Unexecute() = 0;
};
