#pragma once
#include "../Core/EditorModule.h"
#include "Runtime/Containers/THashtable.h"
#include "Runtime/Math/FColor.h"
#include <functional>

typedef std::function<int(const std::vector<std::string>&)> TerminalFunction;

class TerminalCommandRegisterer;
class Terminal;

struct TerminalItem
{
	std::string str;

	TerminalItem(const std::string& str)
	{
		this->str = str;
	}
};

class TerminalCommandManager
{
	THashtable<std::string, TerminalFunction, StringHashFunction> functions;

	friend class Terminal;
	friend class TerminalCommandRegisterer;
};

class Terminal : public EditorModule
{
	static TerminalCommandManager* commandManager;

	static Terminal* terminal;

	friend class TerminalCommandRegisterer;

	char inputBuffer[512];

	std::vector<TerminalItem> items;

public:
	Terminal();

	static void Initialize();

	static void Print(const std::string& str);

	virtual void Display() override;

private:
	static int StaticTextEditCallback(ImGuiInputTextCallbackData* data);

	int TextEditCallback(ImGuiInputTextCallbackData* data);

	void ClearConsole();

	void ExecuteCommand();

	static void PrintTerminalError(int errorCode);
};

class TerminalCommandRegisterer
{
	TerminalCommandRegisterer(std::string name, TerminalFunction function)
	{
		if (Terminal::commandManager == nullptr)
		{
			Terminal::commandManager = new TerminalCommandManager;
		}
		Terminal::commandManager->functions.Insert(name, function);
	}
};

#define INVALID_ARG_COUNT 1

/*
int Resolution(std::vector<std::string> args)
{
}

TERMINAL_COMMAND(Resolution);
*/