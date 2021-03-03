#pragma once

// Intended to be used for data about the operating system

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
};