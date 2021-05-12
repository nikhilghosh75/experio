#pragma once

/// <summary>
/// A set of function to be used for data about the operating system/screen
/// </summary>

#include "../Math/FVector2Int.h"

struct FResolution
{
	int width;
	int height;

	FResolution()
	{
		width = 0;
		height = 0;
	}

	FResolution(int width, int height)
	{
		this->width = width;
		this->height = height;
	}
};

class SystemMetrics
{
public:
	static FResolution Resolution();

	static FVector2Int CursorDimensions();
};