#pragma once

// Enums specific to windows

enum EWindowResizeType
{
	Resize = 0, // Normal Resize
	Minimize = 1, // When Minimized is clicked
	Maximize = 2, // When Maximized is clicked
	Create = 3 // When the window is created
};