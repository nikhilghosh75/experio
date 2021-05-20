#pragma once

#include "Runtime/Math/ColorPalette.h"
#include "Runtime/Math/FColor.h"
#include "Runtime/Math/FVector2.h"
#include <string>
#include <vector>

enum class EFlowchartNodeShape : uint8_t
{
	Circle,
	Square,
	Triangle,
	Hexagon,
	Octagon,
};

class FlowchartNode
{
public:
	FColor color = ColorPalette::MistBlue;
	FVector2 position;
	FVector2 size = FVector2(30.f, 30.f);
	std::string name;
	EFlowchartNodeShape shape;
};

class FlowchartTransition
{
	unsigned int fromIndex;
	unsigned int toIndex;
	FColor color;
};

class Flowchart
{
public:
	std::vector<FlowchartNode> nodes;
	std::vector<FlowchartTransition> transitions;
};