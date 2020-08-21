#pragma once
#include "ImageReader.h"

class TGAReader : public ImageReader
{
public:
	TGAReader();

	ImageData* ReadFile(const char* fileName) override;
};