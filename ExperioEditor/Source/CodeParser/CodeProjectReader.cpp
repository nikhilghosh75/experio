#include "CodeProjectReader.h"
#include "LCodeParser.h"
#include <sstream>
#include "Runtime/Containers/LString.h"
#include "Runtime/Debug/Debug.h"

#define PB_CODE_PROJECT_NUM_ATTRIBUTES 2

CodeProject CodeProjectReader::ReadFromFile(const std::string& filepath)
{
	CodeProject project;

	std::ifstream inFile(filepath);
	std::string str;
	str.reserve(256);

	for (int i = 0; i < PB_CODE_PROJECT_NUM_ATTRIBUTES; i++)
	{
		ParseGlobalAttribute(project, inFile);
	}

	while (inFile >> str)
	{
		if (str == "Classes:")
		{
			ParseClasses(project, inFile);
		}
		else if (str == "Enums:")
		{
			ParseEnums(project, inFile);
		}
		else if (str == "Functions:")
		{
			ParseFunctions(project, inFile);
		}
	}

	project.generated = true;
	return project;
}

void CodeProjectReader::ParseGlobalAttribute(CodeProject& project, std::ifstream& inFile)
{
	std::string str;
	inFile >> str;

	if (str == "Language:")
	{
		inFile >> str;
		project.codingLanguage = LCodeParser::StringToCodingLanguage(str);
	}
	else if (str == "Filepath:")
	{
		inFile >> project.filepath;
	}
	else
	{
		Debug::LogError("Code Project Global Attribute is not supported");
	}
}

void CodeProjectReader::ParseClasses(CodeProject & project, std::ifstream & inFile)
{
	std::string str;
	
	inFile >> str;

	while (inFile >> str)
	{
		if (str == "}]")
		{
			break;
		}

		CodeClass codeClass;

		// Name
		inFile >> str;
		inFile >> codeClass.name;
		
		// Filename
		inFile >> str;
		inFile >> codeClass.filename;

		// Params
		inFile >> str >> str;
		if (str != "[]")
		{
			std::stringstream ss;
			while (str != "]")
			{
				inFile >> str;
				ss << " " << str;
			}
			ParseParams(codeClass, ss.str(), project.codingLanguage);
		}

		// Functions
		inFile >> str >> str;
		if (str != "[]")
		{
			std::stringstream ss;
			while (str != "]")
			{
				inFile >> str;
				ss << " " << str;
			}
			ParseFunctions(codeClass, ss.str(), project.codingLanguage);
		}

		// Inheritance
		inFile >> str;
		uint8_t numInheritance;
		inFile >> numInheritance;
		for (size_t i = 0; i < numInheritance; i++)
		{
			inFile >> str;
			codeClass.inheritance.push_back(str);
		}

		project.PushClass(codeClass);
		inFile >> str;
	}
}

void CodeProjectReader::ParseParams(CodeClass & codeClass, const std::string & str, ECodingLanguage language)
{
	bool insideQuote = false;
	size_t lastQuote = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '"')
		{
			if (insideQuote)
			{
				CodeParam param = LCodeParser::ParseCodeParam(str.substr(lastQuote + 1, i - lastQuote - 2), language);
				codeClass.params.push_back(param);
			}
			else
			{
				lastQuote = i;
			}
			insideQuote = !insideQuote;
		}
	}
}

void CodeProjectReader::ParseFunctions(CodeClass & codeClass, const std::string & str, ECodingLanguage language)
{
	bool insideQuote = false;
	size_t lastQuote = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '"')
		{
			if (insideQuote)
			{
				CodeFunction codeFunction = LCodeParser::ParseCodeFunction(str.substr(lastQuote + 1, i - lastQuote - 2), language);
				codeClass.functions.push_back(codeFunction);
			}
			else
			{
				lastQuote = i;
			}
			insideQuote = !insideQuote;
		}
	}
}

void CodeProjectReader::ParseEnums(CodeProject & project, std::ifstream & inFile)
{
	std::string str;

	inFile >> str;

	while (str != "}]")
	{
		CodeEnum codeEnum;

		// Name
		inFile >> str >> codeEnum.name;

		// Values
		inFile >> str >> str;
		if (str != "[]")
		{
			std::stringstream ss;
			while (str != "]")
			{
				inFile >> str;
				ss << " " << str;
			}
			ParseValues(codeEnum, ss.str());
		}
	}
}

void CodeProjectReader::ParseValues(CodeEnum & codeEnum, const std::string & str)
{
	size_t lastOpenBrace = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '{')
		{
			lastOpenBrace = i;
		}
		else if (str[i] == '}')
		{
			codeEnum.values.Insert(ParseValue(str.substr(lastOpenBrace + 1, i - lastOpenBrace - 2)));
		}
	}
}

TPair<int, std::string> CodeProjectReader::ParseValue(const std::string & str)
{
	size_t comma = LString::FindFirstOfChar(str, ',');
	std::string name = str.substr(0, comma);
	int value = LString::StringToInt(str.substr(comma + 1));
	return TPair<int, std::string>();
}

void CodeProjectReader::ParseFunctions(CodeProject & project, std::ifstream & inFile)
{
	std::string str;
	inFile >> str;
	if (str != "[]")
	{
		std::stringstream ss;
		while (str != "]")
		{
			inFile >> str;
			ss << " " << str;
		}
		
		bool insideQuote = false;
		size_t lastQuote = 0;
		for (size_t i = 0; i < ss.str().size(); i++)
		{
			if (ss.str()[i] == '"')
			{
				if (insideQuote)
				{
					CodeFunction codeFunction = LCodeParser::ParseCodeFunction(
						ss.str().substr(lastQuote + 1, i - lastQuote - 2), project.codingLanguage);
					project.PushFunction(codeFunction);
				}
				else
				{
					lastQuote = i;
				}
				insideQuote = !insideQuote;
			}
		}
	}
}
