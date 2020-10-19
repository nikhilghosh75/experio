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
