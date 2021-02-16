#include "Terminal.h"
#include "TerminalCommands.h"
#include "Runtime/Containers/LString.h"
#include <sstream>

TerminalCommandManager* Terminal::commandManager;
Terminal* Terminal::terminal;

Terminal::Terminal()
{
	this->name = "Terminal";
	this->category = EEditorModuleCategory::Core;

	terminal = this;

	memset(this->inputBuffer, 0, sizeof(this->inputBuffer));
}

void Terminal::Initialize()
{
	if (Terminal::commandManager == nullptr)
	{
		Terminal::commandManager = new TerminalCommandManager;
	}

	Terminal::commandManager->functions.Insert("add-layer", AddLayer);
	Terminal::commandManager->functions.Insert("add-tag", AddTag);
}

void Terminal::Print(const std::string & str)
{
	terminal->items.emplace_back(str);
}

void Terminal::Display()
{
	ImGui::Text("Console");

	if (ImGui::Button("Clear"))
	{
		ClearConsole();
	}

	// The footer includes one Input Text
	float footerHeight = ImGui::GetFrameHeightWithSpacing();
	ImGui::BeginChild("Scrolling Region", ImVec2(0, -footerHeight), false, ImGuiWindowFlags_HorizontalScrollbar);

	ImGuiListClipper clipper;
	clipper.Begin(items.size());

	while (clipper.Step())
	{
		for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
		{
			ImGui::Text(items[i].str.c_str());
		}
	}

	ImGui::EndChild();

	ImGuiInputTextFlags flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
	if (ImGui::InputText("##Command", inputBuffer, 512, flags, StaticTextEditCallback))
	{
		if (inputBuffer[0] != 0)
		{
			ExecuteCommand();
		}
	}
}

int Terminal::StaticTextEditCallback(ImGuiInputTextCallbackData * data)
{
	return terminal->TextEditCallback(data);
}

int Terminal::TextEditCallback(ImGuiInputTextCallbackData * data)
{
	return 0;
}

void Terminal::ClearConsole()
{
	items.clear();
}

void Terminal::ExecuteCommand()
{
	std::string inputStr = inputBuffer;

	if (inputStr == "help")
	{
		DisplayHelpMessage();
		memset(this->inputBuffer, 0, sizeof(this->inputBuffer));
		return;
	}

	std::vector<std::string> args = LString::SeperateStringByChar(inputStr, ' ');

	Terminal::Print('\t' + inputStr);

	if (commandManager == nullptr)
		return;

	TerminalFunction function;
	bool found = commandManager->functions.SafeGet(args[0], function);
	if (found)
	{
		int returnValue = function(args);
		if (returnValue != 0)
		{
			PrintTerminalError(returnValue);
		}
	}

	if (!found)
	{
		std::stringstream ss;
		ss << args[0] << " was not found. Type \"help\" to display a list of commands";
		Terminal::Print(ss.str());
	}

	memset(this->inputBuffer, 0, sizeof(this->inputBuffer));
}

void Terminal::DisplayHelpMessage()
{
	Terminal::Print("\thelp");
	Terminal::Print("Here is a list of all commands you can access:");
	std::vector<std::string> programs = commandManager->functions.GetKeys();

	for (uint32_t i = 0; i < programs.size(); i++)
	{
		Terminal::Print("  " + programs[i]);
	}

	Terminal::Print("");
}

void Terminal::PrintTerminalError(int errorCode)
{
	switch (errorCode)
	{
	case 1: Terminal::Print("Invalid Argument Count. There are either too many or too few arguments."); break;
	case 2: Terminal::Print("Invalid Arguments."); break;
	default: Terminal::Print("Error Unknown"); break;
	}
}
