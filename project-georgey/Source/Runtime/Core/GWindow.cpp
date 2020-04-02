#include "GWindow.h"
#include "../Debug/GDebug.h"
#include "../Debug/TempProfiler.h"
#include <GL/glew.h>
#include <GL/GL.h>

#ifdef PLATFORM_WINDOWS
LRESULT CALLBACK WindowsProcedure(HWND window, int wm, WPARAM wParam, LPARAM lParam);
#endif

void GWindow::InstantiateWindow()
{
#ifdef PLATFORM_WINDOWS
	WNDCLASSEX wc{};

	HWND hwnd;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)WindowsProcedure;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = "Sample Window Class";
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.style = CS_OWNDC;

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

void GWindow::OnUpdate()
{
#ifdef PLATFORM_WINDOWS
	MSG msg;
	isActive = GetMessage(&msg, NULL, 0, 0); // Change null to hwnd
	TranslateMessage(&msg);
	DispatchMessage(&msg);
#endif
}

void GWindow::CloseWindow()
{
#ifdef PLATFORM_WINDOWS
	PostQuitMessage(0);
#endif
}

#ifdef PLATFORM_WINDOWS
LRESULT WindowsProcedure(HWND window, int message, WPARAM wParam, LPARAM lParam)
{
	GDebug::Log(to_string(message));
	switch (message)
	{
	case WM_CREATE:
	{
		TempProfiler profiler("Creating");
		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
			PFD_TYPE_RGBA, //RGBA framebuffer
			32, // Colordepth of the framebuffer
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24, // Number of bits of the depthbuffer
			8, // Number of bits for the stencilbuffer
			0, // Number of Aux buffers in the framebuffer
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};
		HDC deviceContextHandle = GetDC(window);
		int pixelFormat = ChoosePixelFormat(deviceContextHandle, &pfd);
		SetPixelFormat(deviceContextHandle, pixelFormat, &pfd);

		HGLRC openGLRenderingContext = wglCreateContext(deviceContextHandle);
		wglMakeCurrent(deviceContextHandle, openGLRenderingContext);
		GLenum error = glewInit();
	}
		break;
	default:
		return DefWindowProc(window, message, wParam, lParam);
	}
	return 0;
}
#endif