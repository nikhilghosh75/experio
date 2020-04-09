#pragma once
#include "../Base/GSingleton.h"
#include <string>
#include <vector>
#include "Core.h"
#include <Windows.h>
#include "../Input/GInput.h"
#include "WindowEnums.h"
using namespace std;

struct FWindowData
{
	string title;
	int width;
	int height;

	FWindowData(const string& newTitle = "Project Bloo", int newWidth = 1280, int newHeight = 720)
	{
		title = newTitle;
		width = newWidth;
		height = newHeight;
	}
};

//Used to transmit window data specific to the platform
struct FPlatformWindowData
{
#ifdef PLATFORM_WINDOWS
	HWND hwnd;
#endif
};

class GWindow
{
#ifdef PLATFORM_WINDOWS
	HWND hwnd;
#endif

public:
	GWindow();

	void InstantiateWindow();
	void OnUpdate();
	void CloseWindow();

	bool isActive;

	static void ReceiveInput(EInputType inputType, unsigned int param1, unsigned int param2=0, unsigned int param3=0);
	static void ResizeWindow(EWindowResizeType resizeType, int width, int height);

private:
	GInput input;
};