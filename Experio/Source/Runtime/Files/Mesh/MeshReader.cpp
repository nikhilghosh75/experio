#include "MeshReader.h"
#include "BinMeshReader.h"
#include "OBJReader.h"
#include "../LFileOperations.h"
#include "../../Debug/Debug.h"
#include "../../Framework/AssetMap.h"

MeshData * MeshReader::ReadFile(const char * fileName)
{
	std::string extension = LFileOperations::GetExtension(fileName);

	if (extension == "obj")
	{
		OBJReader reader;
		return reader.ReadFile(fileName);
	}
	else if (extension == "pbbmesh")
	{
		BinMeshReader reader;
		return reader.ReadFile(fileName);
	}

	Debug::LogError("Mesh File was not recognized");
	return nullptr;
}

MeshData * MeshReader::ReadFile(unsigned int assetIndex)
{
	std::string filepath;
	if (AssetMap::assetMap.SafeGet(assetIndex, filepath))
	{
		return MeshReader::ReadFile(filepath.c_str());
	}
	return nullptr;
}
