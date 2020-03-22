#pragma once
#include <string>
#include "Core.h"
#include <Windows.h>
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

class GWindow
{
public:
	void InstantiateWindow();
};