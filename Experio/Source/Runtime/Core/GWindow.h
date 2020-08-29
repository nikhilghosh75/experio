#pragma once
#include <string>
#include <vector>
#include "Core.h"
#include <Windows.h>
#include "../Input/Input.h"
#include "WindowEnums.h"
using namespace std;

#define PB_KEYPRESSED		0x9675
#define PB_KEYRELEASED		0x9676
#define PB_LEFTMOUSE		0x9677
#define PB_RIGHTMOUSE		0x9678
#define PB_MIDDLEMOUSE		0x9679
#define PB_MOUSEWHEEL		0x9680
#define PB_MOUSEMOVE		0x9681
#define PB_BUTTONUP			0x9800
#define PB_BUTTONDOWN		0x9801

struct FWindowData
{
	string title;
	int width;
	int height;

	FWindowData()
	{
		title = "";
		width = 0;
		height = 0;
	}

	FWindowData(int newWidth, int newHeight, const string& newTitle = "Project Bloo")
	{
		title = newTitle;
		width = newWidth;
		height = newHeight;
	}
};

class GWindow
{
#ifdef PLATFORM_WINDOWS
	HWND* hwnd;
#endif
	static FWindowData windowData;
	static GWindow* instance;
public:
	GWindow();

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
	static GWindow* Get() { return instance; }

	static void CallViewport();

#ifdef PLATFORM_WINDOWS
	HWND* GetHWND();
#endif
private:
	Input input;
};