#pragma once

#include "MeshReader.h"
#include <fstream>

class BinMeshReader : MeshReader
{
public:
	MeshData* ReadFile(const char* fileName);

private:
	static uint8_t GetNumOfChuncks(uint16_t flags);

	static void ReadVertexChunck(std::ifstream& stream, uint32_t numVerticies, MeshData* meshData);

	static void ReadUVChunck(std::ifstream& stream, uint32_t numVerticies, MeshData* meshData);

	static void ReadNormalChunck(std::ifstream& stream, uint32_t numVerticies, MeshData* meshData);

	static void ReadTangentChunck(std::ifstream& stream, uint32_t numVerticies, MeshData* meshData);

	static void ReadBitangentChunck(std::ifstream& stream, uint32_t numVerticies, MeshData* meshData);

	static void ReadIndexChunck(std::ifstream& stream, uint32_t numIndicies, uint8_t indexType, MeshData* meshData);
};