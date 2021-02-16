#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Math/FColor.h"

// To-Do: Rename Later
class TimeProfilerStamp
{
public:
	std::string name;
	ImU32 color;
	int level;
	float start;
	float end;

	TimeProfilerStamp();
	TimeProfilerStamp(std::string name, ImU32 color, int level, float start, float end);
};

class TimeProfilerData
{
	std::vector<TimeProfilerStamp> stamps;

public:
	static TimeProfilerData ReadFromFile(const std::string& filepath);

	static ImU32 CategoryToColor(uint32_t category);
};

class TimeProfiler : public EditorModule
{
	float zoom = 2;
	float position = 0;
	float endPosition = 0;
	float millisecondWidth = 0;

	ImVec2 canvasStart;
	ImVec2 canvasSize;
	ImVec2 canvasEnd;

	void DisplayMenuBar();
	void DisplayCanvas();
	void DisplayLines();

	void ProfilerBar(const std::string& name, ImU32 color, int level, float start, float end);

public:
	TimeProfiler();

	virtual void Display() override;
	
	virtual void HandleInput() override;
};