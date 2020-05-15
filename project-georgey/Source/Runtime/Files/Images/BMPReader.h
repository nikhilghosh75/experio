#pragma once
#include "ImageReader.h"

class BMPReader : ImageReader
{
public:
	BMPReader();

	ImageData* ReadFile(const char* fileName) override;
};