#include "BinFontReader.h"
#include "../../Debug/Debug.h"
#include "../../Debug/Profiler.h"
#include "../../Framework/AssetMap.h"
#include "../../Rendering/Managers/TextureManager.h"
#include <fstream>

FontData * BinFontReader::ReadFile(const char * fileName)
{
	PROFILE_SCOPE_CATEGORY("Reading Binary Font", EProfilerCategory::Files);

	std::ifstream inFile(fileName, std::ios::binary);

	char check[9];
	inFile.read(check, 8);
	check[8] = '\n';
	if (strcmp(check, "PBBFONT ") != 0)
	{
		Debug::LogError("Incorrect File Format");
		return nullptr;
	}

	FontData* font = new FontData();

	char header[52];
	inFile.read(header, 52);

	font->encoding = (ETextEncoding) *(uint8_t*)&(header[0]);
	font->charset = (ECharacterSet) *(uint8_t*)&(header[1]);
	uint32_t numCharacters = *(uint32_t*)&(header[4]);
	font->defaultFontSize = *(int*)&(header[8]);
	uint32_t textureID = *(uint32_t*)&(header[28]);
	font->fontTexture = TextureManager::LoadTexture(AssetMap::assetMap.Get(textureID));
	font->name = std::string(&(header[32]));

	font->characters.reserve(numCharacters);
	for (size_t i = 0; i < numCharacters; i++)
	{
		char charData[32];
		inFile.read(charData, 32);

		FCharacterInfo character;
		character.charCode = *(uint32_t*)&(charData[0]);
		character.xAdvance = *(int*)&(charData[4]);
		character.uvCoordinates = *(FRect*)&(charData[8]);
		character.offset = *(FVector2*)&(charData[24]);
		font->characters.push_back(character);
	}

	return font;
}
