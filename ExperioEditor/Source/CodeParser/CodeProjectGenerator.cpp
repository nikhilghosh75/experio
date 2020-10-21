#include "CodeProjectGenerator.h"
#include "LCodeParser.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Math/FVector2Int.h"
#include "Runtime/Containers/LString.h"
#include <fstream>
#include <sstream>

void CodeProjectGenerator::ParseFile(std::string filepath)
{
	std::ifstream stream(filepath);

	if (stream.fail())
	{
		Debug::LogError("File " + filepath + " could not be opened");
	}

	FileBuffer buffer = LFileOperations::ReadFileToBuffer(stream, 256);
	std::vector<FVector2Int> vector = GetObjectsInCodeFile(buffer);
	ParseObjectsInCodeFile(vector, buffer);
	Debug::log << filepath << " " << buffer[20] << " " << buffer.Size() << Debug::endl;
}

bool CodeProjectGenerator::IsValidFile(std::string filepath) const
{
	if (!LCodeParser::IsFilepathOfLanguage(project->codingLanguage, filepath))
	{
		return false;
	}
	return true;
}

CodeProjectGenerator::CodeProjectGenerator()
{
	this->project = nullptr;
}

CodeProjectGenerator::CodeProjectGenerator(CodeProject * project)
{
	this->project = project;
	this->rootFilepath = project->filepath;
	this->iterator = fs::recursive_directory_iterator(this->rootFilepath);
}

CodeProjectGenerator::CodeProjectGenerator(std::string & rootFilepath, CodeProject * project)
{
	this->rootFilepath = rootFilepath;
	this->project = project;
	this->iterator = fs::recursive_directory_iterator(rootFilepath);
}

void CodeProjectGenerator::GenerateFullProject()
{
	while (currentlyGenerating)
	{
		StepGenerate();
	}
}

void CodeProjectGenerator::StepGenerate()
{
	if (!currentlyGenerating) return;
	iterator++;
	if (iterator == fs::end(iterator))
	{
		currentlyGenerating = false;
		project->generated = true;
		return;
	}

	std::string filepath = iterator->path().string();
	if (IsValidFile(filepath))
	{
		ParseFile(filepath);
	}
}

// Start and Stop of Enums, Classes, Structs
std::vector<FVector2Int> CodeProjectGenerator::GetObjectsInCodeFile(FileBuffer & buffer)
{
	std::vector<FVector2Int> returnVector;
	for (int i = 0; i < buffer.Size() - 1; i++)
	{
		// Single Line Comment
		if (buffer[i] == '/' && buffer[i + 1] == '/')
		{
			while (i < buffer.Size() && buffer[i] != '\n')
			{
				i++;
			}
		}
		// Multi Line Comment
		else if (buffer[i] == '/' && buffer[i + 1] == '*')
		{
			while (i < buffer.Size() + 1 && buffer[i] != '*' && buffer[i + 1] != '/')
			{
				i++;
			}
		}
		// Tokens
		else if (LCodeParser::IsEnumToken(buffer, i, project->codingLanguage)
			|| LCodeParser::IsClassToken(buffer, i, project->codingLanguage))
		{
			size_t foundPosition = i;
			bool isForwardDeclaration = false;
			while (buffer[i] != '{')
			{
				if (buffer[i] == ';')
				{
					isForwardDeclaration = true;
					break;
				}
				i++;
			}

			if (isForwardDeclaration) continue;

			uint8_t scopeDepth = 1;
			while (scopeDepth != 0)
			{
				i++;
				if (buffer[i] == '{') scopeDepth++;
				else if (buffer[i] == '}') scopeDepth--;
			}
			returnVector.push_back(FVector2Int(foundPosition, i));
		}
	}
	return returnVector;
}

void CodeProjectGenerator::ParseObjectsInCodeFile(std::vector<FVector2Int>& objects, FileBuffer & buffer)
{
	for (int i = 0; i < objects.size(); i++)
	{
		FVector2Int object = objects[i];
		if (LCodeParser::IsEnumToken(buffer, object.x, project->codingLanguage))
		{
			ParseEnumInCodeFile(object, buffer);
		}
		else if (LCodeParser::IsClassToken(buffer, object.x, project->codingLanguage))
		{
			// Parse Classes Here
		}
	}
}

void CodeProjectGenerator::ParseEnumInCodeFile(FVector2Int location, FileBuffer & buffer)
{
	CodeEnum codeEnum;
	codeEnum.dataType = EEnumDataType::NONE;
	// Check Enum Data Type
	size_t i = location.x;
	while (buffer[i] != ':' && buffer[i] != '{')
	{
		i++;
	}

	if (buffer[i] == ':')
	{
		codeEnum.name = GetNameFromEnd(i, buffer);
		while (buffer[i] != '{')
		{
			i++;
		}
		codeEnum.dataType = LCodeParser::GetEnumDataType(GetNameFromEnd(i, buffer), project->codingLanguage);
	}
	else if (buffer[i] == '{')
	{
		codeEnum.name = GetNameFromEnd(i, buffer);
	}

	// Get Each Key/Value Pair
	int currentValue = 0;
	int lastComma = i + 1;
	while (buffer[i] != '}' && i <= location.y)
	{
		if (buffer[i] == ',')
		{
			std::string name;
			int value;
			LCodeParser::GetEnumNameValue(buffer.Substr(lastComma, i), currentValue, name, value);
			codeEnum.values.Insert(value, name);
			lastComma = i + 1;
		}
		i++;
	}

	// Check for errors
	if (codeEnum.dataType == EEnumDataType::NONE)
	{
		codeEnum.dataType = LCodeParser::GetEnumDataType(codeEnum.values.GetSize());
	}
	project->enums.push_back(codeEnum);
}

void CodeProjectGenerator::ParseClassInCodeFile(FVector2Int location, FileBuffer & buffer)
{
	int i = location.x;
	// Inheritance (if any)

	// Figure out if member or function
}

std::string CodeProjectGenerator::GetNameFromEnd(size_t endOfName, FileBuffer & buffer)
{
	size_t i = endOfName - 2;
	while (!LString::IsWhitespace(buffer[i]))
	{
		i--;
	}

	return buffer.Substr(i, endOfName - 1);
}
