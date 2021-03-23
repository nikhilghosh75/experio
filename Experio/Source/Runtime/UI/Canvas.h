#pragma once

class Canvas
{
	friend class Window;
	friend class EditorWindow;

	static float canvasHeight;
	static float canvasWidth;

	static void UpdateWindow(float height, float width);

public:
	static float GetCanvasHeight();
	static float GetCanvasWidth();
};