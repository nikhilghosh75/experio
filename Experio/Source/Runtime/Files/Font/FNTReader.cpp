#include "FNTReader.h"
#include "LFontOperations.h"
#include "../LFileOperations.h"
#include "../../Rendering/Texture.h"
#include "../../Debug/Debug.h"
#include "../../Debug/Profiler.h"
#include "../../Containers/LString.h"

FNTReader::FNTReader()
{

}

FontData * FNTReader::ReadFile(const char * fileName)
{
	PROFILE_SCOPE_CATEGORY("FNT Reader", EProfilerCategory::Files);

	std::ifstream fntStream(fileName);
	if (fntStream.fail())
	{
		Debug::LogError("FNT File " + (std::string)fileName + " could not be opened");
		return 0;
	}

	FontData* returnData = new FontData();

	float textureWidth;
	float textureHeight;

	std::string word;
	unsigned int currentCharacter = 0;

	while (fntStream >> word)
	{
		if (word.find("face=") != std::string::npos)
		{
			returnData->name = StripQuotes(StripAfterEqualSign(word));
		}
		else if (word.find("charset=") != std::string::npos)
		{
			returnData->charset = ParseCharacterSet(word);
		}
		else if (word.find("scaleW=") != std::string::npos)
		{
			textureWidth = atof(StripAfterEqualSign(word).c_str());
		}
		else if (word.find("scaleH=") != std::string::npos)
		{
			textureHeight = atof(StripAfterEqualSign(word).c_str());
		}
		else if (word.find("file=") != std::string::npos)
		{
			std::string imageFileName = StripQuotes(StripAfterEqualSign(word));
			std::string fileLocation = LFileOperations::GetDirectory(fileName);
			std::string imageFilePath = (std::string)fileLocation + "/" + imageFileName;
			returnData->fontTexture = TextureManager::LoadTexture(imageFilePath);
		}
		else if (word.find("count=") != std::string::npos)
		{
			std::string countString = StripAfterEqualSign(word);
			int count = atoi(countString.c_str());
			returnData->characters.resize((size_t)count + returnData->characters.size() + 1);
		}
		else if (word.find("lineHeight=") != std::string::npos)
		{
			std::string lineHeightString = StripAfterEqualSign(word);
			returnData->defaultFontSize = LString::StringToInt(lineHeightString);
		}
		else if (word == "char")
		{
			FCharacterInfo characterInfo = ReadCharacterData(fntStream, textureWidth, textureHeight);
			returnData->characters[currentCharacter] = characterInfo;
			currentCharacter++;
		}
	}

	returnData->encoding = LFontOperations::GetEncoding(*returnData);
	LFontOperations::SortCharacters(*returnData);

	return returnData;
}

size_t FNTReader::SerializedSizeOf(const char * fileName)
{
	std::ifstream fntStream(fileName);
	if (fntStream.fail())
	{
		Debug::LogError("FNT File " + (std::string)fileName + " could not be opened");
		return 0;
	}

	std::string word;
	while (fntStream >> word)
	{
		if (word == "chars")
		{
			fntStream >> word;
			uint32_t numCharacters = LString::StringToUInt(word);
			return LFontOperations::SerializedSizeOf(numCharacters);
		}
	}

	return 0;
}

std::string FNTReader::StripAfterEqualSign(const std::string& s)
{
	size_t equalsPosition = s.find("=");
	if (equalsPosition == std::string::npos)
	{
		return s;
	}
	return s.substr(equalsPosition + 1);
}

std::string FNTReader::StripQuotes(const std::string & s)
{
	std::string returnString = s;
	if (s[0] == '"')
	{
		returnString = s.substr(1);
	}
	if (s[s.length() - 1] == '"')
	{
		returnString = returnString.substr(0, returnString.length() - 1);
	}
	return returnString;
}

ECharacterSet FNTReader::ParseCharacterSet(const std::string& s)
{
	std::string charSet = StripAfterEqualSign(s);
	if (charSet.length() == 2)
	{
		return ECharacterSet::ANSI;
	}
	return ECharacterSet();
}

FCharacterInfo FNTReader::ReadCharacterData(std::ifstream & fntStream, float width, float height)
{
	FCharacterInfo characterInfo;
	FRect uvRect;

	std::string word;
	fntStream >> word;

	// ID
	word = StripAfterEqualSign(word);
	characterInfo.charCode = atoi(word.c_str());

	// X
	fntStream >> word;
	word = StripAfterEqualSign(word);
	float temp = atof(word.c_str());
	uvRect.min.x = atof(word.c_str()) / width;

	// Y
	fntStream >> word;
	word = StripAfterEqualSign(word);
	temp = atof(word.c_str());
	uvRect.min.y = atof(word.c_str()) / height;

	// Width
	fntStream >> word;
	word = StripAfterEqualSign(word);
	temp = atof(word.c_str());
	uvRect.max.x = (atof(word.c_str()) / width) + uvRect.min.x;

	// Height
	fntStream >> word;
	word = StripAfterEqualSign(word);
	temp = atof(word.c_str());
	uvRect.max.y = (atof(word.c_str()) / height) + uvRect.min.y;

	// XOffset
	fntStream >> word;
	word = StripAfterEqualSign(word);
	characterInfo.offset.x = atof(word.c_str());

	// YOffset
	fntStream >> word;
	word = StripAfterEqualSign(word);
	characterInfo.offset.y = atof(word.c_str());

	// XAdvance
	fntStream >> word;
	word = StripAfterEqualSign(word);
	characterInfo.xAdvance = atoi(word.c_str());

	uvRect.Fix();

	characterInfo.uvCoordinates = uvRect;
	return characterInfo;
}