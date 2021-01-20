#include "TimeProfiler.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Math/LMath.h"

#define PB_MILLISECOND_WIDTH 12.f;
#define PB_ZOOM_MIN 0.25f
#define PB_ZOOM_MAX 10
#define PB_SCROLL_SPEED 0.005f

void TimeProfiler::DisplayCanvas()
{
	canvasStart = ImGui::GetCursorScreenPos();      
	canvasSize = ImGui::GetContentRegionAvail();
	if (canvasSize.x < 50) canvasSize.x = 50;
	if (canvasSize.y < 50) canvasSize.y = 50;
	canvasEnd = ImVec2(canvasStart.x + canvasSize.x, canvasStart.y + canvasSize.y);

	// Canvas
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	draw_list->AddRectFilled(canvasStart, canvasEnd, IM_COL32(50, 50, 50, 255));
	draw_list->AddRect(canvasStart, canvasEnd, IM_COL32(255, 255, 255, 255));
}

void TimeProfiler::DisplayLines()
{
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	float timestep = 0.001f;
	float stepWidth = zoom * PB_MILLISECOND_WIDTH;

	if (stepWidth < 15.f)
	{
		timestep = 0.01f;
		stepWidth *= 10.f;
	}

	for (float i = LMath::FMod(position, stepWidth); i < canvasSize.x; i += stepWidth)
	{
		draw_list->AddLine(ImVec2(canvasStart.x + i, canvasStart.y), ImVec2(canvasStart.x + i, canvasEnd.y), IM_COL32(200, 200, 200, 40));
	}
}

TimeProfiler::TimeProfiler()
{
	this->category = EEditorModuleCategory::Profiling;
	this->name = "Time Profiler";
}

void TimeProfiler::Display()
{
	ImGui::Text(std::to_string(position).c_str());
	DisplayCanvas();
	DisplayLines();
}

void TimeProfiler::HandleInput()
{
	ImGuiIO& io = ImGui::GetIO();
	float scrollY = io.MouseWheel;
	if (scrollY > 0.1f && zoom < PB_ZOOM_MAX)
	{
		zoom += 0.125f;
	}
	else if (scrollY < -0.1f && zoom > PB_ZOOM_MIN)
	{
		zoom -= 0.125f;
	}

	float millisecondWidth = zoom * PB_MILLISECOND_WIDTH;
	if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
	{
		this->position = LMath::Max(position - io.MouseDelta.x * millisecondWidth * PB_SCROLL_SPEED, 0.f);
	}
}
