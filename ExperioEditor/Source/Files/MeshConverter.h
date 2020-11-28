#pragma once
#include <string>

class MeshConverter
{
public:
	static void ConvertMeshToBinary(const std::string& fromFilepath, const std::string& toFilepath);

private:
	static uint8_t GetIndexType(uint32_t numVerticies);
};