#pragma once
#include <string>
#include <vector>
#include "Core.h"
#include <Windows.h>
#include "../Input/Input.h"

#define PB_KEYPRESSED		0x9675
#define PB_KEYRELEASED		0x9676
#define PB_LEFTMOUSE		0x9677
#define PB_RIGHTMOUSE		0x9678
#define PB_MIDDLEMOUSE		0x9679
#define PB_MOUSEWHEEL		0x9680
#define PB_MOUSEMOVE		0x9681
#define PB_BUTTONUP			0x9800
#define PB_BUTTONDOWN		0x9801

enum class EWindowResizeType
{
	Resize = 0, // Normal Resize
	Minimize = 1, // When Minimized is clicked
	Maximize = 2, // When Maximized is clicked
	Create = 3 // When the window is created
};

enum class EWindowAxisType
{
	None = 0,
	X = 1,
	Y = 2
};

struct FWindowData
{
	std::string title;
	int width;
	int height;

	FWindowData()
	{
		title = "";
		width = 0;
		height = 0;
	}

	FWindowData(int newWidth, int newHeight, const std::string& newTitle = "Project Bloo")
	{
		title = newTitle;
		width = newWidth;
		height = newHeight;
	}
};

class Window
{
#ifdef PLATFORM_WINDOWS
	HWND* hwnd;
#endif
	static FWindowData windowData;
	static Window* instance;
public:
	Window();

	~Window();

	void InstantiateWindow();
	void OnUpdate();
	void MakeContext();
	void CloseWindow();

	bool isActive;

	bool SetSwapInterval(int interval);

	static void ReceiveInput(EInputType inputType, unsigned int param1, unsigned int param2=0, unsigned int param3=0);
	static void ResizeWindow(EWindowResizeType resizeType, int width, int height);
	static EMouseButton GetMouseButton(unsigned int mouseEnum);

	static FWindowData GetWindowData();
	static Window* Get() { return instance; }

	static void CallViewport();

#ifdef PLATFORM_WINDOWS
	HWND* GetHWND();
#endif
private:
	Input input;
};