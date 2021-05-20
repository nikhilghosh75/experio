#include "FlowchartViewer.h"
#include "FlowchartReader.h"
#include "FlowchartSaver.h"
#include "Runtime/Containers/Algorithm.h"
#include "Runtime/Math/LMath.h"
#include "Runtime/Rendering/ImGui/LImGui.h"
#include "../Core/FileDialog.h"

static const float SELECTED_THICKNESS = 5.0f;
#define PB_ZOOM_MIN 0.125f
#define PB_ZOOM_MAX 30

FlowchartViewer::FlowchartViewer()
{
	this->name = "Flowchart Viewer";
	this->category = EEditorModuleCategory::Viewer;
	this->flags = ImGuiWindowFlags_MenuBar;
}

void FlowchartViewer::Display()
{
	DisplayMenu();

	DisplayUpperMenu();
	DisplayCanvas();
	DisplayNodes();
}

void FlowchartViewer::HandleInput()
{
	ImGuiIO& io = ImGui::GetIO();
	float scrollY = io.MouseWheel;
	if (scrollY > 0.1f && zoomFactor < PB_ZOOM_MAX)
	{
		zoomFactor += 0.125f;
	}
	else if (scrollY < -0.1f && zoomFactor > PB_ZOOM_MIN)
	{
		zoomFactor -= 0.125f;
	}
}

void FlowchartViewer::DisplayMenu()
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New Flowchart"))
			{
				flowchart.nodes.clear();
				flowchart.transitions.clear();
			}
			if (ImGui::MenuItem("Open Flowchart"))
			{
				FFileDialogInfo info = FileDialog::OpenFile("Experio Flowchart(*pbflow)\0*.pbflow\0");
				if (info.IsValid())
					flowchart = FlowchartReader::ReadFlowchart(info.filename);
			}
			if (ImGui::MenuItem("Save Flowchart"))
			{
				FFileDialogInfo info = FileDialog::SaveFile("Experio Flowchart(*pbflow)\0*.pbflow\0");
				if (info.IsValid())
					FlowchartSaver::SaveFlowchart(flowchart, info.filename);
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Add Node"))
			{
				flowchart.nodes.emplace_back();
			}
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}
}

void FlowchartViewer::DisplayUpperMenu()
{
	ImGui::DragFloat("Zoom:", &zoomFactor, 0.125, 0.125, 10);

	if (currentlySelectedIndex < 0)
		return;

	FlowchartNode& node = flowchart.nodes[currentlySelectedIndex];

	// Shape Buttons
	if (ImGui::Button("Circle"))
		node.shape = EFlowchartNodeShape::Circle;
	ImGui::SameLine();
	if (ImGui::Button("Square"))
		node.shape = EFlowchartNodeShape::Square;
	ImGui::SameLine();
	if (ImGui::Button("Triangle"))
		node.shape = EFlowchartNodeShape::Triangle;

	ImGui::SameLine(); ImGui::Separator(); ImGui::SameLine();
	ImGui::PushItemWidth(320);
	ImGui::ColorEdit4("##NodeColor", (float*)(FColor*)(&node.color), ImGuiColorEditFlags_Float);
	ImGui::PopItemWidth();
	ImGui::SameLine(); ImGui::Separator(); ImGui::SameLine();

	ImGui::PushItemWidth(180);
	ImGui::DragFloat2("Size", (float*)(FVector2*)&node.size);
	ImGui::PopItemWidth();
	ImGui::SameLine(); ImGui::Separator(); ImGui::SameLine();

	if (ImGui::Button("Delete"))
	{
		Experio::Algorithm::RemoveAt(flowchart.nodes, currentlySelectedIndex);
		currentlySelectedIndex = -1;
	}
}

void FlowchartViewer::DisplayCanvas()
{
	canvasStart = ImGui::GetCursorScreenPos();

	canvasSize = ImGui::GetContentRegionAvail();
	if (canvasSize.x < 50) canvasSize.x = 50;
	if (canvasSize.y < 50) canvasSize.y = 50;
	canvasEnd = ImVec2(canvasStart.x + canvasSize.x, canvasStart.y + canvasSize.y);

	// Canvas
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	drawList->AddRectFilled(canvasStart, canvasEnd, IM_COL32(50, 50, 50, 255));
	drawList->AddRect(canvasStart, canvasEnd, IM_COL32(255, 255, 255, 255));

	ImGui::InvisibleButton("canvas", canvasSize, ImGuiButtonFlags_MouseButtonLeft | ImGuiButtonFlags_MouseButtonRight);
	bool isActive = ImGui::IsItemActive();

	ImGuiIO& io = ImGui::GetIO();
	float mouseThresholdForDrag = -1.0f;
	if (isActive && ImGui::IsMouseDragging(ImGuiMouseButton_Right) && !isDraggingShape)
	{
		topLeftCorner.x += io.MouseDelta.x;
		topLeftCorner.y += io.MouseDelta.y;
	}

	clickedThisFrame = isActive && ImGui::IsMouseClicked(ImGuiMouseButton_Left);

	float GRID_STEP = 64.0f * zoomFactor;
	for (float x = fmodf(topLeftCorner.x, GRID_STEP); x < canvasSize.x; x += GRID_STEP)
		drawList->AddLine(ImVec2(canvasStart.x + x, canvasStart.y), ImVec2(canvasStart.x + x, canvasEnd.y), IM_COL32(200, 200, 200, 40));
	for (float y = fmodf(topLeftCorner.y, GRID_STEP); y < canvasSize.y; y += GRID_STEP)
		drawList->AddLine(ImVec2(canvasStart.x, canvasStart.y + y), ImVec2(canvasEnd.x, canvasStart.y + y), IM_COL32(200, 200, 200, 40));
}

void FlowchartViewer::DisplayNodes()
{
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	isDraggingShape = false;
	clickedOnShape = false;

	for (size_t i = 0; i < flowchart.nodes.size(); i++)
	{
		DisplayNode(drawList, flowchart.nodes[i], i);
	}

	if (clickedThisFrame && !clickedOnShape)
		currentlySelectedIndex = -1;
}

void FlowchartViewer::DisplayNode(ImDrawList* drawList, FlowchartNode& node, size_t index)
{
	ImVec2 nodeStart = ImVec2(canvasStart.x + node.position.x + topLeftCorner.x, canvasStart.y + node.position.y + topLeftCorner.y);
	ImVec2 nodeEnd = ImVec2(nodeStart.x + node.size.x * zoomFactor, nodeStart.y + node.size.y * zoomFactor);
	ImVec2 nodeCenter = ImVec2((nodeStart.x + nodeEnd.x) / 2, (nodeStart.y + nodeEnd.y) / 2);

	switch (node.shape)
	{
	case EFlowchartNodeShape::Square:
		drawList->AddRectFilled(nodeStart, nodeEnd, (uint32_t)node.color);
		if(index == currentlySelectedIndex)
			drawList->AddRect(nodeStart, nodeEnd, IM_COL32(255, 255, 255, 255), 0, 15, SELECTED_THICKNESS);
		break;
	case EFlowchartNodeShape::Circle:
		drawList->AddCircleFilled(nodeCenter, nodeEnd.x - nodeStart.x, (uint32_t)node.color);
		if(index == currentlySelectedIndex)
			drawList->AddCircle(nodeCenter, nodeEnd.x - nodeStart.x, IM_COL32(255, 255, 255, 255), 0, SELECTED_THICKNESS);
		break;
	case EFlowchartNodeShape::Triangle:
		drawList->AddTriangleFilled(nodeStart, ImVec2(nodeCenter.x, nodeEnd.y), ImVec2(nodeEnd.x, nodeStart.y), (uint32_t)node.color);
		if(index == currentlySelectedIndex)
			drawList->AddTriangle(nodeStart, ImVec2(nodeCenter.x, nodeEnd.y), ImVec2(nodeEnd.x, nodeStart.y), IM_COL32(255, 255, 255, 255), SELECTED_THICKNESS);
		break;
	}

	ImGuiIO& io = ImGui::GetIO();
	if (io.MousePos.x > nodeStart.x && io.MousePos.x < nodeEnd.x && io.MousePos.y > nodeStart.y && io.MousePos.y < nodeEnd.y)
	{
		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		{
			currentlySelectedIndex = index;
			clickedOnShape = true;
		}

		if (ImGui::IsMouseDragging(ImGuiMouseButton_Left) && (currentlySelectedIndex < 0 || currentlySelectedIndex == index))
		{
			node.position.x += io.MouseDelta.x;
			node.position.y += io.MouseDelta.y;
			isDraggingShape = true;
		}
		else
		{
			isDraggingShape = false;
		}
	}
}
