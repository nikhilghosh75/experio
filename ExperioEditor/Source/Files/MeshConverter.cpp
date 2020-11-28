#include "MeshConverter.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Rendering/Managers/MeshManager.h"

void MeshConverter::ConvertMeshToBinary(const std::string & fromFilepath, const std::string & toFilepath)
{
	if (LFileOperations::GetFileType(fromFilepath) != EAssetType::Mesh)
	{
		Debug::LogError("From Filepath is not a correct filepath");
		return;
	}

	if (!LFileOperations::DoesFileHaveExtension(toFilepath, ".pbbmesh"))
	{
		Debug::LogError("To Filepath is not a correct filemesh");
		return;
	}

	MeshRef ref = MeshManager::LoadMesh(fromFilepath);

	std::ofstream outFile(toFilepath, std::ios::out | std::ios::binary);

	outFile.write("PBBMESH ", 8);

	uint16_t flags = 64;
	uint32_t numVerticies = ref->verticies->GetCount();
	uint32_t numIndicies = ref->indexBuffer->GetCount();
	uint8_t indexType = GetIndexType(numVerticies);

	outFile.write((char*)&flags, 2);
	outFile.write((char*)&indexType, 1);
	outFile.write("0", 1);
	outFile.write((char*)&numVerticies, 4);
	outFile.write((char*)&numIndicies, 4);

	// Verticies
	VertexBuffer* verticies = ref->verticies;
	outFile.write("VERT", 4);
	outFile.write((char*)verticies->GetData(), verticies->GetSize());

	// UVs
	VertexBuffer* uvs = ref->uv;
	outFile.write("UVS ", 4);
	outFile.write((char*)uvs->GetData(), uvs->GetSize());

	// Normals
	VertexBuffer* normals = ref->normals;
	outFile.write("NORM", 4);
	outFile.write((char*)normals->GetData(), normals->GetSize());

	// Tangents
	VertexBuffer* tangents = ref->tangents;
	outFile.write("TANG", 4);
	outFile.write((char*)tangents->GetData(), tangents->GetSize());

	// Bitangents
	VertexBuffer* bitangents = ref->bitangents;
	outFile.write("BITG", 4);
	outFile.write((char*)bitangents->GetData(), bitangents->GetSize());

	// Indicies
	IndexBuffer* indicies = ref->indexBuffer;
	outFile.write("INDX", 4);
	unsigned int* data = indicies->GetData();
	for (uint32_t i = 0; i < indicies->GetCount(); i++)
	{
		switch (indexType)
		{
		case 1:
		{
			uint8_t index = data[i];
			outFile.write((char*)&index, 1);
			break;
		}
		case 2:
		{
			uint16_t index = data[i];
			outFile.write((char*)&index, 2);
			break;
		}
		case 4:
		{
			uint32_t index = data[i];
			outFile.write((char*)&index, 4);
			break;
		}
		}
	}
}

uint8_t MeshConverter::GetIndexType(uint32_t numVerticies)
{
	if (numVerticies < 256)
	{
		return 1;
	}
	if (numVerticies < 65535)
	{
		return 2;
	}
	return 4;
}
