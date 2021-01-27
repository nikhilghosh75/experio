#include "BinMeshReader.h"
#include "../../Debug/Debug.h"
#include "../../Debug/Profiler.h"
#include "../../Math/Math.h"

MeshData * BinMeshReader::ReadFile(const char * fileName)
{
	PROFILE_SCOPE_CATEGORY("Reading Binary Mesh", EProfilerCategory::Files);

	std::ifstream inFile(fileName, std::ios::binary);

	char check[9];
	inFile.read(check, 8);
	check[8] = '\n';
	if (strcmp(check, "PBBMESH ") != 0)
	{
		Debug::LogError("Incorrect File Format");
		return nullptr;
	}

	char header[12];
	inFile.read(header, 12);

	uint16_t flags = *(uint16_t*)&(header[0]);
	uint8_t indexType = *(uint8_t*)&(header[2]);
	uint32_t numVerticies = *(uint32_t*)&(header[4]);
	uint32_t numIndicies = *(uint32_t*)&(header[8]);
	uint8_t numChuncks = GetNumOfChuncks(flags);

	MeshData* meshData = new MeshData();
	meshData->isIndexed = false;

	for (uint8_t i = 0; i < numChuncks; i++)
	{
		char chunckHeader[4];
		inFile.read(chunckHeader, 4);

		if (chunckHeader[0] == 'V' && chunckHeader[1] == 'E' && chunckHeader[2] == 'R' && chunckHeader[3] == 'T')
		{
			ReadVertexChunck(inFile, numVerticies, meshData);
		}
		else if (chunckHeader[0] == 'U' && chunckHeader[1] == 'V' && chunckHeader[2] == 'S' && chunckHeader[3] == ' ')
		{
			ReadUVChunck(inFile, numVerticies, meshData);
		}
		else if (chunckHeader[0] == 'N' && chunckHeader[1] == 'O' && chunckHeader[2] == 'R' && chunckHeader[3] == 'M')
		{
			ReadNormalChunck(inFile, numVerticies, meshData);
		}
		else if (chunckHeader[0] == 'T' && chunckHeader[1] == 'A' && chunckHeader[2] == 'N' && chunckHeader[3] == 'G')
		{
			ReadTangentChunck(inFile, numVerticies, meshData);
		}
		else if (chunckHeader[0] == 'B' && chunckHeader[1] == 'I' && chunckHeader[2] == 'T' && chunckHeader[3] == 'G')
		{
			ReadBitangentChunck(inFile, numVerticies, meshData);
		}
		else if (chunckHeader[0] == 'I' && chunckHeader[1] == 'N' && chunckHeader[2] == 'D' && chunckHeader[3] == 'X')
		{
			ReadIndexChunck(inFile, numIndicies, indexType, meshData);
		}
	}

	return nullptr;
}

uint8_t BinMeshReader::GetNumOfChuncks(uint16_t flags)
{
	// Add stuff here
	uint8_t numChuncks = 0;
	if (flags == 64)
	{
		return 6;
	}

	return numChuncks;
}

void BinMeshReader::ReadVertexChunck(std::ifstream& stream, uint32_t numVerticies, MeshData* meshData)
{
	FVector3* verticies = new FVector3[numVerticies];
	stream.read((char*)verticies, numVerticies * sizeof(FVector3));

	meshData->verticies = new VertexBuffer(verticies, numVerticies * sizeof(FVector3), EDataType::FLOAT);
}

void BinMeshReader::ReadUVChunck(std::ifstream & stream, uint32_t numVerticies, MeshData * meshData)
{
	FVector2* uvs = new FVector2[numVerticies];
	stream.read((char*)uvs, numVerticies * sizeof(FVector2));

	meshData->uv = new VertexBuffer(uvs, numVerticies * sizeof(FVector2), EDataType::FLOAT);
}

void BinMeshReader::ReadNormalChunck(std::ifstream & stream, uint32_t numVerticies, MeshData * meshData)
{
	FVector3* normals = new FVector3[numVerticies];
	stream.read((char*)normals, numVerticies * sizeof(FVector3));

	meshData->normals = new VertexBuffer(normals, numVerticies * sizeof(FVector3), EDataType::FLOAT);
}

void BinMeshReader::ReadTangentChunck(std::ifstream & stream, uint32_t numVerticies, MeshData * meshData)
{
	FVector3* tangents = new FVector3[numVerticies];
	stream.read((char*)tangents, numVerticies * sizeof(FVector3));

	meshData->tangents = new VertexBuffer(tangents, numVerticies * sizeof(FVector3), EDataType::FLOAT);
}

void BinMeshReader::ReadBitangentChunck(std::ifstream & stream, uint32_t numVerticies, MeshData * meshData)
{
	FVector3* bitangents = new FVector3[numVerticies];
	stream.read((char*)bitangents, numVerticies * sizeof(FVector3));

	meshData->bitangents = new VertexBuffer(bitangents, numVerticies * sizeof(FVector3), EDataType::FLOAT);
}

void BinMeshReader::ReadIndexChunck(std::ifstream & stream, uint32_t numIndicies, uint8_t indexType, MeshData * meshData)
{
	unsigned int* indicies = new unsigned int[numIndicies];
	char indexString[16];
	for (uint32_t i = 0; i < numIndicies; i++)
	{
		switch (indexType)
		{
		case 1:
		{
			stream.read(indexString, 1);
			uint8_t index = *(uint8_t*)&(indexString[0]);
			indicies[i] = index;
			break;
		}
		case 2:
		{
			stream.read(indexString, 2);
			uint16_t index = *(uint16_t*)&(indexString[0]);
			indicies[i] = index;
			break;
		}
		case 4:
		{
			stream.read(indexString, 4);
			uint32_t index = *(uint8_t*)&(indexString[0]);
			indicies[i] = index;
			break;
		}
		}
	}

	meshData->indexBuffer = new IndexBuffer(indicies, numIndicies);
	meshData->isIndexed = true;
}
