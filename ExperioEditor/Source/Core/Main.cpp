#include <Windows.h>
#include <stdio.h>
#include "GL/glew.h"
#include <gl/GL.h>
#include "GL/wglext.h"
#include <tchar.h>
#include "imgui.h"
#include "examples/imgui_impl_win32.h"
#include "examples/imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include "Core/EditorWindow.h"
#include "Runtime/Core/Window.h"

int main(int argc, char** argv)
{
	EditorWindow::InitializeWindow();

	while (EditorWindow::isActive)
	{
		EditorWindow::BeginFrame();

		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();

		EditorWindow::EndFrame();
	}
	
	EditorWindow::CloseWindow();
}