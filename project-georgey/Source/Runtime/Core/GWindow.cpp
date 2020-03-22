#include "GWindow.h"

#ifdef PLATFORM_WINDOWS
LRESULT CALLBACK WindowsProcedure(HWND window, int wm, WPARAM wParam, LPARAM lParam);
#endif

void GWindow::InstantiateWindow()
{
#ifdef PLATFORM_WINDOWS
	WNDCLASSEX wc{};

	MSG mesg;
	HWND hwnd;
	wc.lpfnWndProc = (WNDPROC)WindowsProcedure;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = "Sample Window Class";
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		return;
	}

	hwnd = CreateWindowEx(0, "Sample Window Class", "Test", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);

	if (!hwnd)
	{
		return;
	}

	ShowWindow(hwnd, SW_SHOW);
#endif
}

#ifdef PLATFORM_WINDOWS
LRESULT WindowsProcedure(HWND window, int wm, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(window, wm, wParam, lParam);
}
#endif