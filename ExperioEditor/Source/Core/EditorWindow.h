#pragma once
#include "Runtime/Core/Window.h"
#include <Windows.h>

class EditorWindow
{
	static HWND hwnd;
	static int displayWidth, displayHeight;

public:
	static bool isActive;

	static void InitializeWindow();
	static void BeginFrame();
	static void EndFrame();
	static void CloseWindow();
	static bool SetSwapInterval(int interval);

	static void OnResize(int width, int height);
};