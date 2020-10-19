#include "CodeProjectGenerator.h"
#include "LCodeParser.h"
#include "Runtime/Debug/Debug.h"
#include "Runtime/Files/LFileOperations.h"
#include "Runtime/Math/FVector2Int.h"
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

// Start and Stop of Enums, Classes, Structs, Functions
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
		else if (LCodeParser::IsEnumToken(buffer, i, project->codingLanguage))
		{
			size_t foundPosition = i;
			while (buffer[i] != '{')
			{
				i++;
			}

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
