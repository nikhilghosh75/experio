#include "CompilationParser.h"
#include "Runtime/Containers/LString.h"

std::vector<std::string> CompilationParser::compiledFiles;
std::vector<CppCompilationError> CompilationParser::compilationErrors;
std::string CompilationParser::currentString = " ";
ECompilationParseStage CompilationParser::currentStage;

bool CompilationParser::isCompiling = false;

#define PB_MAX_OUTPUT_LENGTH 65535

void CompilationParser::Initialize()
{
	currentString.reserve(PB_MAX_OUTPUT_LENGTH);
}

void CompilationParser::Reset()
{
	compiledFiles.clear();
	compilationErrors.clear();
	currentString = " ";
	currentStage = ECompilationParseStage::CommandListing;
}

void CompilationParser::StartCompilation()
{
	Reset();
	isCompiling = true;
}

void CompilationParser::StopCompilation()
{
	isCompiling = false;
}

bool CompilationParser::CompilationSuccessful()
{
	for (int i = 0; i < compilationErrors.size(); i++)
	{
		if (compilationErrors[i].IsError())
			return false;
	}
	return true;
}

void CompilationParser::Read(char * buffer)
{
	if (!isCompiling)
		return;

	switch (currentStage)
	{
	case ECompilationParseStage::CommandListing:
	{
		std::string bufferStr = std::string(buffer);
		size_t echoPosition = bufferStr.find("echo");
		if (echoPosition != std::string::npos)
		{
			currentString += bufferStr.substr(0, echoPosition);
			ParseCommandOutput();
			currentString = "" + bufferStr.substr(echoPosition + 5);
		}
		else
		{
			currentString += bufferStr;
		}
	}
		break;
	case ECompilationParseStage::DeveloperOutput:
	{
		std::string bufferStr = std::string(buffer);
		if (bufferStr != "\r\n" && bufferStr[5] != '*' && bufferStr.find("Visual Studio") == std::string::npos)
		{
			currentStage = ECompilationParseStage::FileListing;
		}
	}
		return;
	case ECompilationParseStage::FileListing:
	{
		std::string bufferStr = std::string(buffer);
		compiledFiles = LString::SeperateStringByChar(bufferStr, '\n');
		currentStage = ECompilationParseStage::ErrorOutput;
	}
		return;
	case ECompilationParseStage::ErrorOutput:
	{
		std::string bufferStr = std::string(buffer);
		std::vector<std::string> errorStrs = LString::SeperateStringByChar(bufferStr, '\n');

		if (errorStrs.size() == 0)
			return;

		for (size_t i = 0; i < errorStrs.size() - 1; i++)
		{
			if (errorStrs[i].size() == 0)
				continue;
			if (errorStrs[i][0] != 'c' || errorStrs[i][0] != 'C')
				continue;
			if (!LString::HasChar(errorStrs[i], ':'))
				continue;
			if (LString::NumOfCharsFront(errorStrs[i], ' ') >= 8)
				continue;

			compilationErrors.emplace_back(errorStrs[i]);
		}
	}
		return;
	}
}

void CompilationParser::ParseCommandOutput()
{
	currentStage = ECompilationParseStage::DeveloperOutput;
}
