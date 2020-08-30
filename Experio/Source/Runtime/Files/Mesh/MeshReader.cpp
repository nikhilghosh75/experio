#include "MeshReader.h"
#include "OBJReader.h"
#include "../LFileOperations.h"
#include "../../Debug/Debug.h"

MeshData * MeshReader::ReadFile(const char * fileName)
{
	std::string extension = LFileOperations::GetExtension(fileName);

	if (extension == "obj")
	{
		OBJReader reader;
		return reader.ReadFile(fileName);
	}

	Debug::LogError("Mesh File was not recognized");
	return nullptr;
}
