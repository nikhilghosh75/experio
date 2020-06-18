#pragma once
#include "ImageReader.h"

class TGAReader : ImageReader
{
	TGAReader();

	ImageData* ReadFile(const char* fileName) override;
};