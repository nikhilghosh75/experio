#pragma once

#include "MeshReader.h"

class OBJReader : MeshReader
{
public:
	MeshData* ReadFile(const char* fileName);

	size_t SerializedSizeOf(const char* filename);
};