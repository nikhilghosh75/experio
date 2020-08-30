#include "FNTReader.h"
#include "../../Rendering/Texture.h"
#include "../../Debug/Debug.h"
#include "../../Debug/TempProfiler.h"
#include "../../Containers/LString.h"

FNTReader::FNTReader()
{

}

FontData * FNTReader::ReadFile(const char * fileName)
{
	TempProfiler profiler("FNT Reader");
	FontData* returnData = new FontData();
	returnData->fileType = EFontFileType::FNT;

	ifstream fntStream(fileName);
	if (fntStream.fail())
	{
		Debug::LogError("FNT File " + (std::string)fileName + " could not be opened");
		return 0;
	}

	float textureWidth;
	float textureHeight;

	std::string word;
	unsigned int currentCharacter = 0;

	while (fntStream >> word)
	{
		if (word.find("face=") != string::npos)
		{
			returnData->name = StripQuotes(StripAfterEqualSign(word));
		}
		else if (word.find("charset=") != string::npos)
		{
			returnData->charset = ParseCharacterSet(word);
		}
		else if (word.find("scaleW=") != string::npos)
		{
			textureWidth = atof(StripAfterEqualSign(word).c_str());
		}
		else if (word.find("scaleH=") != string::npos)
		{
			textureHeight = atof(StripAfterEqualSign(word).c_str());
		}
		else if (word.find("file=") != string::npos)
		{
			std::string imageFileName = StripQuotes(StripAfterEqualSign(word));
			std::string fileLocation = LString::GetFileLocation(fileName);
			std::string imageFilePath = (std::string)fileLocation + "/" + imageFileName;
			returnData->fontTexture = new Texture(imageFilePath.c_str());
		}
		else if (word.find("count=") != string::npos)
		{
			std::string countString = StripAfterEqualSign(word);
			int count = atoi(countString.c_str());
			returnData->characters.resize((size_t)count + returnData->characters.size() + 1);
		}
		else if (word == "char")
		{
			FCharacterInfo characterInfo = ReadCharacterData(fntStream, textureWidth, textureHeight);
			returnData->characters[currentCharacter] = characterInfo;
			currentCharacter++;
		}
	}

	return returnData;
}

std::string FNTReader::StripAfterEqualSign(const std::string& s)
{
	size_t equalsPosition = s.find("=");
	if (equalsPosition == string::npos)
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
		return ECharacterSet::UNICODE;
	}
	return ECharacterSet();
}

FCharacterInfo FNTReader::ReadCharacterData(ifstream & fntStream, float width, float height)
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