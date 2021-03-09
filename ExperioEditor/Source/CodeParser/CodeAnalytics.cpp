#include "CodeAnalytics.h"
#include "LCodeParser.h"
#include "Runtime/Files/LFileOperations.h"
#include <filesystem>
#include <fstream>
namespace fs = std::filesystem;

CodeAnalytics::CodeAnalytics()
{
	Clear();
}

void CodeAnalytics::Clear()
{
	this->numFiles = 0;
	this->numLines = 0;

	this->numClasses = 0;
	this->numEnums = 0;
	this->numFunctions = 0;

	this->numComponents = 0;
	this->numLibraries = 0;
}

void CalculateNumLines(CodeAnalytics& analytics, const CodeProject& project)
{
	for (auto& p : fs::recursive_directory_iterator(project.filepath))
	{
		std::string filepath = p.path().string();
		if (!LCodeParser::IsFilepathOfLanguage(project.codingLanguage, filepath))
		{
			continue;
		}

		std::ifstream stream(filepath);
		FileBuffer buffer = LFileOperations::ReadTrimmedFileToBuffer(stream);
		analytics.numLines += buffer.NumOfCharacter('\n');
		analytics.numFiles++;
	}
}

void CalculateExperioSpecificInfo(CodeAnalytics& analytics, const CodeProject& project)
{
	// Calculate Number of Components
	analytics.numComponents = LCodeParser::NumInheritsFrom(project, "Component");

	// Calculate Number of Libraries
	for (auto& p : fs::recursive_directory_iterator(project.filepath))
	{
		std::string filepath = p.path().string();
		if (!LCodeParser::IsFilepathOfLanguage(project.codingLanguage, filepath))
		{
			continue;
		}

		std::ifstream stream(filepath);
		FileBuffer buffer = LFileOperations::ReadTrimmedFileToBuffer(stream);
		if (buffer.Find("EXPERIO_LIBRARY", 40) != std::string::npos)
		{
			analytics.numLibraries++;
		}
	}
}

void GenerateCodeAnalyticsFromProject(CodeAnalytics& analytics, const CodeProject& project)
{
	analytics.Clear();

	analytics.numClasses = project.classes.size();
	analytics.numEnums = project.enums.size();
	analytics.numFunctions = project.functions.size();

	CalculateNumLines(analytics, project);
	CalculateExperioSpecificInfo(analytics, project);
}
