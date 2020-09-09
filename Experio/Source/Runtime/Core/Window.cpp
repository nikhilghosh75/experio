#include "Window.h"
#include "../Debug/Debug.h"
#include "../Debug/TempProfiler.h"
#include "../Math/LMath.h"
#include "../Rendering/LOpenGL.h"
#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include "GL/wglext.h"
#include <thread>

#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include <tchar.h>

#ifdef PLATFORM_WINDOWS
LRESULT CALLBACK WindowsProcedure(HWND window, int wm, WPARAM wParam, LPARAM lParam);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

HDC deviceContext;
HGLRC openGLRenderingContext;

FWindowData Window::windowData;
Window* Window::instance;

Window::Window()
{
	instance = this;
}

Window::~Window()
{
#ifdef PLATFORM_WINDOWS
	DestroyWindow(*hwnd);
#endif
}

void Window::InstantiateWindow()
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
	windowData.title = "Test";

	if (!hwnd)
	{
		return;
	}

	ShowWindow(hwnd, SW_SHOW);
	this->hwnd = &hwnd;
#endif

	this->isActive = true;
}

void Window::OnUpdate()
{
#ifdef PLATFORM_WINDOWS
	//ShowWindow(this->hwnd, SW_SHOW);
	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//isActive = GetMessage(&msg, NULL, 0, 0); // Change null to hwnd

	HDC deviceContextHandle = GetDC(*this->hwnd);
	wglMakeCurrent(deviceContextHandle, openGLRenderingContext);
	SwapBuffers(deviceContext);
#endif
}

void Window::MakeContext()
{
	HDC deviceContextHandle = GetDC(*this->hwnd);
	wglMakeCurrent(deviceContextHandle, openGLRenderingContext);
}

void Window::CloseWindow()
{
#ifdef PLATFORM_WINDOWS
	PostQuitMessage(0);
#endif
}

bool Window::SetSwapInterval(int interval)
{
	if (LOpenGL::WGLExtensionSupported("WGL_EXT_swap_control"))
	{
		// Extension is supported, init pointers.
		PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");

		// this is another function from WGL_EXT_swap_control extension
		PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");

		wglSwapIntervalEXT(interval);
		return true;
	}
	return false;
}

void Window::ReceiveInput(EInputType inputType, unsigned int param1, unsigned int param2, unsigned int param3)
{
	switch (inputType)
	{
	case EInputType::Keyboard:
		switch (param1)
		{
		case PB_KEYPRESSED:
			Input::OnKeyPressed(param2);
			break;
		case PB_KEYRELEASED:
			Input::OnKeyReleased(param2);
			break;
		}
		break;
	case EInputType::Mouse:
		switch (param1)
		{
		case PB_BUTTONDOWN:
			Input::OnMouseButtonDown(GetMouseButton(param2));
			break;
		case PB_BUTTONUP:
			Input::OnMouseButtonUp(GetMouseButton(param2));
			break;
		case PB_MOUSEMOVE:
			Input::OnMouseMove(FVector2(param2, param3));
			break;
		case PB_MOUSEWHEEL:
			Input::OnMouseScroll((float)param2);
		}
		break;
	}
}

void Window::ResizeWindow(EWindowResizeType resizeType, int width, int height)
{
	glViewport(0, 0, width, height);
	windowData.width = width;
	windowData.height = height;
#ifdef PLATFORM_WINDOWS

#endif
}

EMouseButton Window::GetMouseButton(unsigned int mouseEnum)
{
	switch (mouseEnum)
	{
	case PB_LEFTMOUSE:
		return EMouseButton::Left;
	case PB_MIDDLEMOUSE:
		return EMouseButton::Middle;
	case PB_RIGHTMOUSE:
		return EMouseButton::Right;
	}
	return EMouseButton::Left;
}

FWindowData Window::GetWindowData()
{
	return windowData;
}

void Window::CallViewport()
{
	glViewport(0, 0, windowData.width, windowData.height);
}

#ifdef PLATFORM_WINDOWS
HWND* Window::GetHWND()
{
	return this->hwnd;
}
#endif

#ifdef PLATFORM_WINDOWS
LRESULT WindowsProcedure(HWND window, int message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wParam, lParam))
	{
		return true;
	}

	Debug::Log(std::to_string(message));
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
			Debug::LogError("PIXEL FORMAT FAILED");
		}
		bool setFormat = SetPixelFormat(deviceContextHandle, pixelFormat, &pfd);
		if (!setFormat)
		{
			Debug::LogError("SET PIXEL FORMAT FAILED");
		}
		openGLRenderingContext = wglCreateContext(deviceContextHandle);
		wglMakeCurrent(deviceContextHandle, openGLRenderingContext);
		GetClientRect(window, &rect);
		glViewport(0, 0, rect.right - rect.left, rect.bottom - rect.top);
		GLenum error = glewInit();
		Window::ResizeWindow(EWindowResizeType::Create, rect.right - rect.left, rect.bottom - rect.top);
	}
		break;
	case WM_DESTROY:
	{
		Window::Get()->isActive = false;
		// Implement Application Close Here
	}
	case WM_SIZE:
	{
		std::thread worker(Window::ResizeWindow, (EWindowResizeType)wParam , lParam % LMath::PowOfTwo(16), lParam / LMath::PowOfTwo(16));
		worker.detach();
		break;
	}
	case WM_KEYDOWN:
	{
		std::thread worker(Window::ReceiveInput, EInputType::Keyboard, PB_KEYPRESSED, wParam, 0);
		worker.detach();
		break;
	}
	case WM_KEYUP:
	{
		std::thread worker(Window::ReceiveInput, EInputType::Keyboard, PB_KEYRELEASED, wParam, 0);
		worker.detach();
		break;
	}
	case WM_LBUTTONDOWN:
	{
		std::thread worker(Window::ReceiveInput, EInputType::Mouse, PB_BUTTONDOWN, PB_LEFTMOUSE, 0);
		worker.detach();
		break;
	}
	case WM_LBUTTONUP:
	{
		std::thread worker(Window::ReceiveInput, EInputType::Mouse, PB_BUTTONUP, PB_LEFTMOUSE, 0);
		worker.detach();
		break;
	}
	case WM_MBUTTONDOWN:
	{
		std::thread worker(Window::ReceiveInput, EInputType::Mouse, PB_BUTTONDOWN, PB_MIDDLEMOUSE, 0);
		worker.detach();
		break;
	}
	case WM_MBUTTONUP:
	{
		std::thread worker(Window::ReceiveInput, EInputType::Mouse, PB_BUTTONUP, PB_MIDDLEMOUSE, 0);
		worker.detach();
		break;
	}
	case WM_RBUTTONDOWN:
	{
		std::thread worker(Window::ReceiveInput, EInputType::Mouse, PB_BUTTONDOWN, PB_RIGHTMOUSE, 0);
		worker.detach();
		break;
	}
	case WM_RBUTTONUP:
	{
		std::thread worker(Window::ReceiveInput, EInputType::Mouse, PB_BUTTONUP, PB_RIGHTMOUSE, 0);
		worker.detach();
		break;
	}
	case WM_MOUSEMOVE:
	{
		std::thread worker(Window::ReceiveInput, EInputType::Mouse, PB_MOUSEMOVE, lParam % LMath::PowOfTwo(16), lParam / LMath::PowOfTwo(16));
		worker.detach();
		break;
	}
	case WM_MOUSEWHEEL:
	{
		std::thread worker(Window::ReceiveInput, EInputType::Mouse, PB_MOUSEWHEEL, GET_WHEEL_DELTA_WPARAM(wParam), 0);
	}
	default:
		return DefWindowProc(window, message, wParam, lParam);
	}
	return 0;
}
#endif