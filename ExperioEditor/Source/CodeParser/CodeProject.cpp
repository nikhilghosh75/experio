#include "CodeProject.h"
#include "CodeProjectGenerator.h"

FCodeProjectOptions FCodeProjectOptions::defaultOptions;

FCodeProjectOptions::FCodeProjectOptions()
{
	this->codingLanguage = ECodingLanguage::CPlusPlus;
	this->generateInstantly = false;
}

CodeProject::CodeProject()
{
	this->filepath = "";
	this->codingLanguage = ECodingLanguage::None;
}

CodeProject::CodeProject(ECodingLanguage language)
{
	this->filepath = "";
	this->codingLanguage = language;
}

CodeProject::CodeProject(std::string filepath, FCodeProjectOptions & options)
{
	this->filepath = filepath;
	this->codingLanguage = options.codingLanguage;
	
	if (options.generateInstantly)
	{
		Generate();
	}
}

void CodeProject::Generate()
{
	CodeProjectGenerator generator(this);
	generator.GenerateFullProject();
	generated = true;
}

void CodeProject::PushClass(const CodeClass & codeClass)
{
	this->classes.push_back(codeClass);
}

void CodeProject::PushEnum(const CodeEnum & codeEnum)
{
	this->enums.push_back(codeEnum);
}

void CodeProject::PushFunction(const CodeFunction & function)
{
	this->functions.push_back(function);
}

void CodeProject::Empty()
{
	generated = false;
	this->classes.clear();
	this->enums.clear();
	this->functions.clear();
}

CodeClass & CodeProject::EmplaceClass()
{
	return this->classes.emplace_back();
}

CodeClass & CodeProject::EmplaceClass(const std::string & name)
{
	return this->classes.emplace_back(name);
}

CodeEnum & CodeProject::EmplaceEnum()
{
	return this->enums.emplace_back();
}

CodeEnum & CodeProject::EmplaceEnum(const std::string & name)
{
	return this->enums.emplace_back(name);
}

CodeEnum & CodeProject::EmplaceEnum(const std::string & name, EEnumDataType dataType)
{
	return this->enums.emplace_back(name, dataType);
}

CodeFunction & CodeProject::EmplaceFunction()
{
	return this->functions.emplace_back();
}

CodeFunction & CodeProject::EmplaceFunction(const std::string & returnType, const std::string & functionName)
{
	return this->functions.emplace_back(returnType, functionName);
}

uint32_t CodeProject::FindIndexOfClass(const std::string & str) const
{
	for (uint32_t i = 0; i < this->classes.size(); i++)
	{
		if (str == this->classes[i].name) return i;
	}
	return CODE_OBJECT_NOT_FOUND;
}

uint32_t CodeProject::FindIndexOfEnum(const std::string & str) const
{
	for (uint32_t i = 0; i < this->enums.size(); i++)
	{
		if (str == this->enums[i].name) return i;
	}
	return CODE_OBJECT_NOT_FOUND;
}
