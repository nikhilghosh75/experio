#pragma once

#include "Flowchart.h"
#include "../Core/EditorModule.h"

class FlowchartViewer : public EditorModule
{
public:
	static FlowchartViewer* flowchartViewer;

	FlowchartViewer();

	virtual void Display() override;

	virtual void HandleInput() override;

	void SaveCurrentFlowchart();

private:
	ImVec2 canvasStart;
	ImVec2 canvasSize;
	ImVec2 canvasEnd;

	bool isDraggingShape;

	int currentlySelectedIndex = -1;
	bool clickedThisFrame;
	bool clickedOnShape;

	float zoomFactor = 1;

	ImVec2 topLeftCorner;

	Flowchart flowchart;

	void DisplayMenu();

	void DisplayUpperMenu();

	void DisplayCanvas();
	
	void DisplayNodes();
	void DisplayNode(ImDrawList* drawList, FlowchartNode& node, size_t index);
};