#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Runtime/Files/Images/ImageReader.h"

class ImageMetasystem
{
public:
	static void GenerateMetadata(const std::string& filepath, std::ofstream& outFile);

private:
	static EImageCompressionType GetCompression(const std::string& filepath);
};