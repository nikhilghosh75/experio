#define IMGUI_IMPL_OPENGL_LOADER_GLEW
#define IMGUI_DEFINE_MATH_OPERATORS

#ifdef PLATFORM_WINDOWS
	#include <Windows.h>
#endif

#include "imconfig.h"
#include "imgui.h"
#include "imgui_internal.h";
#include "imgui_demo.h"

#include "imgui.cpp";
#include "imgui_demo.cpp"
#include "imgui_draw.cpp";
#include "imgui_widgets.cpp";
#include "examples/imgui_impl_opengl3.cpp";
#include "examples/imgui_impl_win32.cpp";