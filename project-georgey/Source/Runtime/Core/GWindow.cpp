#include "GWindow.h"
#include "../Debug/GDebug.h"
#include "../Debug/TempProfiler.h"
#include "../Math/LMath.h"
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <thread>

#ifdef PLATFORM_WINDOWS
LRESULT CALLBACK WindowsProcedure(HWND window, int wm, WPARAM wParam, LPARAM lParam);
#endif

HDC deviceContext;

GWindow::GWindow()
{
	
}

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
	this->hwnd = hwnd;
#endif
}

void GWindow::OnUpdate()
{
#ifdef PLATFORM_WINDOWS
	ShowWindow(this->hwnd, SW_SHOW);
	MSG msg;
	isActive = GetMessage(&msg, NULL, 0, 0); // Change null to hwnd
	TranslateMessage(&msg);
	DispatchMessage(&msg);
	SwapBuffers(deviceContext);
#endif
}

void GWindow::CloseWindow()
{
#ifdef PLATFORM_WINDOWS
	PostQuitMessage(0);
#endif
}

void GWindow::ReceiveInput(EInputType inputType, unsigned int param1, unsigned int param2, unsigned int param3)
{
	switch (inputType)
	{
	case EInputType::Keyboard:

		break;
	}
}

void GWindow::ResizeWindow(EWindowResizeType resizeType, int width, int height)
{
	glViewport(0, 0, width, height);
#ifdef PLATFORM_WINDOWS

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
		RECT rect;
		GetWindowRect(window, &rect);
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
		deviceContext = deviceContextHandle;
		int pixelFormat = ChoosePixelFormat(deviceContextHandle, &pfd);
		if (pixelFormat == 0)
		{
			GDebug::LogError("PIXEL FORMAT FAILED");
		}
		bool setFormat = SetPixelFormat(deviceContextHandle, pixelFormat, &pfd);
		if (!setFormat)
		{
			GDebug::LogError("SET PIXEL FORMAT FAILED");
		}
		HGLRC openGLRenderingContext = wglCreateContext(deviceContextHandle);
		wglMakeCurrent(deviceContextHandle, openGLRenderingContext);
		GetClientRect(window, &rect);
		glViewport(0, 0, rect.right - rect.left, rect.bottom - rect.top);
		GLenum error = glewInit();
	}
		break;
	case WM_SIZE:
	{
		std::thread worker(GWindow::ResizeWindow, (EWindowResizeType)wParam , lParam % LMath::PowOfTwo(16), lParam / LMath::PowOfTwo(16));
		worker.detach();
		break;
	}
	case WM_KEYDOWN:
		//GDebug::Log(to_string((int)GInput::SystemToKeycode(wParam)));
		break;
	case WM_KEYUP:
		break;
	default:
		return DefWindowProc(window, message, wParam, lParam);
	}
	return 0;
}
#endif