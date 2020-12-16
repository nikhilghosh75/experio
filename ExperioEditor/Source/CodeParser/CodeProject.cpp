#include "CodeProject.h"
#include "CodeProjectGenerator.h"

FCodeProjectOptions FCodeProjectOptions::defaultOptions;

FCodeProjectOptions::FCodeProjectOptions()
{
	this->codingLanguage = ECodingLanguage::CPlusPlus;
	this->generateInstantly = false;
}

CodeProject::CodeProject(std::string filepath, FCodeProjectOptions & options)
{
	this->filepath = filepath;
	this->codingLanguage = options.codingLanguage;
	
	if (options.generateInstantly)
	{
		CodeProjectGenerator generator(this);
		generator.GenerateFullProject();
		generated = true;
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
