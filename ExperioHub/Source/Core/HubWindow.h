#pragma once
#include <Windows.h>

#define PLATFORM_WINDOWS

class HubWindow
{
	static HWND hwnd;
	static int displayWidth, displayHeight;

public:
	static bool isActive;

	static void Initialize();

	static void BeginFrame();

	static void EndFrame();

	static void Close();

	static bool SetSwapInterval(int interval);

#ifdef PLATFORM_WINDOWS
	static HWND GetHWND();
#endif
};