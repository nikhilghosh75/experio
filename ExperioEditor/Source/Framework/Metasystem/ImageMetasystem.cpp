#include "ImageMetasystem.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Files/Images/LImageOperations.h"

void ImageMetasystem::GenerateMetadata(const std::string& filepath, std::ofstream& outFile)
{
	EImageCompressionType compressionType = GetCompression(filepath);
	outFile << LImageOperations::CompressionTypeToString(compressionType) << std::endl;

	// TO-DO: Add support for cubemaps
	outFile << "Cubemap: " << "false" << std::endl;
}

EImageCompressionType ImageMetasystem::GetCompression(const std::string& filepath)
{
	std::string ext = LFileOperations::GetExtension(filepath);
	if (ext == "png")
		return EImageCompressionType::Deflate;

	return EImageCompressionType::None;
}
