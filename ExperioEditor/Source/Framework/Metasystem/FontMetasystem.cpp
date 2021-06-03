#include "FontMetasystem.h"
#include "Runtime/Containers/LString.h"
#include "Runtime/Files/LFileOperations.h"

void FontMetasystem::GenerateMetadata(const std::string& filepath, std::ofstream& outFile)
{
	// Is the image stored in the font file. Depends on the extension
	bool imageStored = false;
	std::string ext = LFileOperations::GetExtension(filepath);
	if (ext == "otf" || ext == "ttf")
		imageStored = true;

	outFile << "FontName: " << "Temp" << std::endl;
	outFile << "ImageStored: " << LString::BoolToString(imageStored) << std::endl;
	outFile << "TextureWidth: " << 512 << std::endl;
	outFile << "TextureHeight: " << 512 << std::endl;
	outFile << "DefaultFontSize: " << 36 << std::endl;
	outFile << "NumFonts: " << 1 << std::endl;
}
