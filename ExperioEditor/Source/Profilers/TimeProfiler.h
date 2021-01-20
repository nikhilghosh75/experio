#pragma once

#include "../Core/EditorModule.h"
#include "Runtime/Math/FColor.h"

class TimeProfiler : public EditorModule
{
	float zoom = 2;
	float position = 0;

	ImVec2 canvasStart;
	ImVec2 canvasSize;
	ImVec2 canvasEnd;

	void DisplayCanvas();
	void DisplayLines();

	void ProfilerBar(const std::string& name, FColor color, int level, float start, float end);

public:
	TimeProfiler();

	virtual void Display() override;
	
	virtual void HandleInput() override;
};