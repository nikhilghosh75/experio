#include "FontConverter.h"
#include "../BuildSystem/AssetMapSaver.h"
#include "../BuildSystem/BinarySaveParams.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Rendering/Managers/FontManager.h"

void FontConverter::ConvertFontToBinary(const std::string & fromFilepath, const std::string & toFilepath)
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

	FontRef ref = FontManager::LoadFont(fromFilepath);

	std::ofstream outFile(toFilepath, std::ios::out | std::ios::binary);

	outFile.write("PBBFONT ", 8);

	uint8_t encoding = (uint8_t)ref->encoding;
	uint8_t charset = (uint8_t)ref->charset;
	uint32_t numCharacters = ref->characters.size();
	uint32_t defaultFontSize = ref->defaultFontSize; // Add Here
	uint32_t textureID = AssetMapSaver::GetIndexOfAsset(TextureManager::GetNameOfTexture(ref->fontTexture));
	const char* name = ref->name.c_str();

	outFile.write((char*)&encoding, 1);
	outFile.write((char*)&charset, 1);
	outFile.write("00", 2);
	outFile.write((char*)&numCharacters, 4);
	outFile.write((char*)&defaultFontSize, 4);
	outFile.write("ABCDEFGHIJKLMNOP", 16);
	outFile.write((char*)&textureID, 4);
	outFile.write(name, 20);

	for (uint32_t i = 0; i < numCharacters; i++)
	{
		uint32_t charCode = ref->characters[i].charCode;
		uint32_t xAdvance = ref->characters[i].xAdvance;
		FRect rect = ref->characters[i].uvCoordinates;
		FVector2 offset = ref->characters[i].offset;

		outFile.write((char*)&charCode, 4);
		outFile.write((char*)&xAdvance, 4);
		outFile.write((char*)&rect, 16);
		outFile.write((char*)&offset, 8);
	}
}
