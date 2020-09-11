#include "EditorWindow.h"
#include <stdio.h>
#include "GL/glew.h"
#include <gl/GL.h>
#include "GL/wglext.h"
#include <tchar.h>
#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_opengl3.h"
#include "imgui_internal.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Rendering/LOpenGL.h"

HWND EditorWindow::hwnd;
int EditorWindow::displayHeight = 0;
int EditorWindow::displayWidth = 0;
bool EditorWindow::isActive = false;

HINSTANCE hInstance;
HGLRC glRenderContext;

LRESULT WINAPI WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void EditorWindow::InitializeWindow()
{
	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName = "NCUI";
	wc.style = CS_OWNDC;
	if (!RegisterClass(&wc))
	{
		Debug::LogError("Class Could not be registered");
		return;
	}

	EditorWindow::hwnd = CreateWindow(wc.lpszClassName, "Experio",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 
		0,
		0,
		640,
		480,
		0,
		0,
		hInstance,
		0
	);

	ShowWindow(EditorWindow::hwnd, SW_SHOWDEFAULT);
	UpdateWindow(EditorWindow::hwnd);

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	HDC deviceContext = GetDC(hwnd);
	int pixelFormat = ChoosePixelFormat(deviceContext, &pfd);
	SetPixelFormat(deviceContext, pixelFormat, &pfd);
	glRenderContext = wglCreateContext(deviceContext);
	wglMakeCurrent(deviceContext, glRenderContext);

	SetSwapInterval(1);
	glewInit();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplWin32_Init(hwnd);

	const char* glsl_version = "#version 130";
	ImGui_ImplOpenGL3_Init(glsl_version);

	ImGui::StyleColorsClassic();

	isActive = true;
}

void EditorWindow::BeginFrame()
{
	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void EditorWindow::EndFrame()
{
	ImGui::Render();
	HDC deviceContext = GetDC(hwnd);
	wglMakeCurrent(deviceContext, glRenderContext);
	glViewport(0, 0, displayWidth, displayHeight);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	wglMakeCurrent(deviceContext, glRenderContext);
	SwapBuffers(deviceContext);
}

void EditorWindow::CloseWindow()
{
	ImGui_ImplOpenGL3_Shutdown();
	wglDeleteContext(glRenderContext);
	ImGui::DestroyContext();
	ImGui_ImplWin32_Shutdown();

	DestroyWindow(hwnd);
	UnregisterClass(_T("NCUI"), hInstance);
}

bool EditorWindow::SetSwapInterval(int interval)
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

void EditorWindow::OnResize(int width, int height)
{
	displayHeight = height;
	displayWidth = width;
}

#ifdef PLATFORM_WINDOWS

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		EditorWindow::OnResize(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_DESTROY:
		EditorWindow::isActive = false;
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

#endif