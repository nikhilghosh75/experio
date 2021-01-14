#pragma once
#include <string>
#include <Windows.h>

class EditorProgressBar
{
	HWND hwndPB;
	bool open = false;

public:
	EditorProgressBar();

	EditorProgressBar(unsigned int numSteps, std::string name = "");

	~EditorProgressBar();

	void SetupBar(unsigned int numSteps, std::string name);

	void Step();

	void Step(unsigned int steps);

	void Close();
};