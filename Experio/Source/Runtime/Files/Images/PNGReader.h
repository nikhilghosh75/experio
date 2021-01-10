#pragma once
#include "ImageReader.h"

class PNGReader
{
public:
	PNGReader();

	ImageData* ReadFile(const char * fileName);
};