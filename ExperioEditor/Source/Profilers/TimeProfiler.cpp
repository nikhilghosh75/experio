#include "TimeProfiler.h"
#include "../Core/FileDialog.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Math/LMath.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include <fstream>

#define PB_MILLISECOND_WIDTH 12.f;
#define PB_ZOOM_MIN 0.25f
#define PB_ZOOM_MAX 10
#define PB_SCROLL_SPEED 0.005f
#define PB_LEVEL_WIDTH 24.f

TimeProfilerStamp::TimeProfilerStamp()
{
	this->name = "";
	this->color = 0;
	this->level = 1;
	this->start = 0.0f;
	this->end = 0.0f;
}

TimeProfilerStamp::TimeProfilerStamp(std::string name, ImU32 color, int level, float start, float end)
{
	this->name = name;
	this->color = color;
	this->level = level;
	this->start = start;
	this->end = end;
}

TimeProfilerData TimeProfilerData::ReadFromFile(const std::string & filepath)
{
	TimeProfilerData data;
	std::ifstream inFile(filepath);

	// Read Start
	uint64_t gameStartTime;
	std::string str;
	inFile >> str >> gameStartTime;

	uint64_t startTime, duration;
	std::string name;
	uint32_t category;
	int threadId;

	while (inFile >> str >> startTime)
	{
		inFile >> str >> duration;
		inFile >> str >> category;
		inFile >> str >> threadId;
		inFile >> str >> name;

		ImU32 color = CategoryToColor(category);
		float floatStart = FDuration::GetMilliseconds(FDuration(startTime - gameStartTime));
		float floatEnd = FDuration::GetMilliseconds(FDuration(duration)) + floatStart;
		data.stamps.emplace_back(name, color, 0, floatStart, floatEnd);
	}

	return data;
}

ImU32 TimeProfilerData::CategoryToColor(uint32_t category)
{
	switch (category)
	{
	case 0: return IM_COL32(128, 128, 128, 255);
	case 1: return IM_COL32(0, 192, 0, 255);
	case 2: return IM_COL32(0, 128, 255, 255);
	case 3: return IM_COL32(255, 128, 0, 255);
	case 4: return IM_COL32(255, 0, 255, 255);
	}
	return 0;
}

void TimeProfiler::DisplayMenuBar()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open"))
			{
				FFileDialogInfo info = FileDialog::OpenFile("Experio Log (*.pblog)\0*.pblog\0");
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Colors"))
		{
			LImGui::DisplayColorSmall(IM_COL32(128, 128, 128, 255), "None");
			LImGui::DisplayColorSmall(IM_COL32(0, 192, 0, 255), "Container");
			LImGui::DisplayColorSmall(IM_COL32(0, 128, 255, 255), "Math");
			LImGui::DisplayColorSmall(IM_COL32(255, 128, 0, 255), "Files");
			LImGui::DisplayColorSmall(IM_COL32(255, 0, 255, 255), "Rendering");
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

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

	// End Position
	millisecondWidth = zoom * PB_MILLISECOND_WIDTH;
	endPosition = position + canvasSize.x / millisecondWidth;
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

void TimeProfiler::ProfilerBar(const std::string & name, ImU32 color, int level, float start, float end)
{
	bool shouldBeDisplayed = start < endPosition && end > position;
	if (!shouldBeDisplayed) return;

	ImDrawList* drawList = ImGui::GetWindowDrawList();

	ImVec2 rectStart = ImVec2(LMath::Max(0.f, (start - position) * millisecondWidth), level * PB_LEVEL_WIDTH);
	// ImVec2 rectEnd = ImVec2(LMath::Min(canvasSize.x, (end - endPosition) * millisecondWidth), (level + 1) * PB_LEVEL_WIDTH);
	ImVec2 rectEnd = ImVec2(canvasSize.x + LMath::Min(0.f, (end - endPosition) * millisecondWidth), (level + 1) * PB_LEVEL_WIDTH);
	drawList->AddRectFilled(ImVec2(canvasStart.x + rectStart.x, canvasStart.y + rectStart.y), 
		ImVec2(canvasStart.x + rectEnd.x, canvasStart.y + rectEnd.y), color);
	drawList->AddText(ImVec2(canvasStart.x + rectStart.x + 4.f, canvasStart.y + rectStart.y + 4.f), IM_COL32_BLACK, name.c_str());
}

TimeProfiler::TimeProfiler()
{
	this->category = EEditorModuleCategory::Profiling;
	this->name = "Time Profiler";

	this->flags = ImGuiWindowFlags_MenuBar;
}

void TimeProfiler::Display()
{
	DisplayMenuBar();
	ImGui::Text(std::to_string(position).c_str());
	ImGui::Text(std::to_string(endPosition).c_str());
	DisplayCanvas();
	DisplayLines();

	ProfilerBar("Application::Run", IM_COL32(225, 30, 30, 255), 1, 0, 45);
	ProfilerBar("ComponentManager::Update", IM_COL32(240, 125, 30, 255), 2, 12, 42);
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

	if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
	{
		this->position = LMath::Max(position - io.MouseDelta.x * millisecondWidth * PB_SCROLL_SPEED, 0.f);
	}
}
