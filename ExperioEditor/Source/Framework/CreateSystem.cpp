#include "CreateSystem.h"
#include "EditorProject.h"
#include "../CodeParser/Cpp/CppCodeStream.h"
#include <fstream>

void CreateSystem::CreateCppClass(const std::string & filepath, ECodeClassBase classType, const std::string & className)
{
	switch (classType)
	{
	case ECodeClassBase::None:
		CreateEmptyClass(filepath, className, ECodingLanguage::CPlusPlus); break;
	case ECodeClassBase::Component:
		CreateComponentClass(filepath, className, ECodingLanguage::CPlusPlus); break;
	case ECodeClassBase::Library:
		CreateLibraryClass(filepath, className, ECodingLanguage::CPlusPlus); break;
	case ECodeClassBase::System:
		CreateSystemClass(filepath, className, ECodingLanguage::CPlusPlus); break;
	}
}

void CreateSystem::CreateDatatable(const std::string& filepath)
{
	std::ofstream outFile(filepath + "/data.csv");
}

void CreateSystem::CreateScene(const std::string & filepath)
{
	std::ofstream outFile(filepath + "/scene.pbscene");
	outFile << "PROJECT BLOO SCENE" << std::endl;
	outFile << "Name: New Scene" << std::endl;
	outFile << "Project: " << EditorProject::projectName << std::endl;
	outFile << "{ " << std::endl;
	outFile << "	Name: Scene Root" << std::endl;
	outFile << "	Transform : 0 0 0 0 0 0 1 1 1 1" << std::endl;
	outFile << "	Tag : 0" << std::endl;
	outFile << "	Layer : 0" << std::endl;
	outFile << "	Components : [{" << std::endl;
	outFile << "		ClassID: 99" << std::endl;
	outFile << "		Params :" << std::endl;
	outFile << "	Children: []" << std::endl;
	outFile << "}]" << std::endl;
}

void CreateSystem::CreateEmptyClass(const std::string & filepath, const std::string & className, ECodingLanguage langauge)
{
	CodeClass codeClass(className);

	switch (langauge)
	{
	case ECodingLanguage::CPlusPlus:
	{
		CppCodeOStream outFile(filepath);
		outFile << codeClass;
	}
		break;
	}
}

void CreateSystem::CreateComponentClass(const std::string & filepath, const std::string & className, ECodingLanguage langauge)
{
	CodeClass codeClass(className);
	codeClass.inheritance.push_back("Component");
	
	CodeFunction startFunction("void", "Start");
	startFunction.accessType = ECodeAccessType::Public;
	startFunction.keywords = ECodeFunctionKeyword::Virtual;
	codeClass.functions.push_back(startFunction);

	CodeFunction updateFunction("void", "Update");
	updateFunction.accessType = ECodeAccessType::Public;
	updateFunction.keywords = ECodeFunctionKeyword::Virtual;
	codeClass.functions.push_back(updateFunction);

	switch (langauge)
	{
	case ECodingLanguage::CPlusPlus:
	{
		CppCodeOStream outFile(filepath);
		outFile << "#include \"Runtime/Framework/Component.h\"" << Debug::endl << Debug::endl;
		outFile << codeClass;
	}
	break;
	}
}

void CreateSystem::CreateSystemClass(const std::string & filepath, const std::string & className, ECodingLanguage langauge)
{
	CodeClass codeClass(className);
	codeClass.inheritance.push_back("System");

	switch (langauge)
	{
	case ECodingLanguage::CPlusPlus:
	{
		CppCodeOStream outFile(filepath);
		outFile << "#include \"Runtime/Framework/System.h\"" << Debug::endl << Debug::endl;
		outFile << codeClass;
	}
	break;
	}
}

void CreateSystem::CreateLibraryClass(const std::string & filepath, const std::string & className, ECodingLanguage langauge)
{
	CreateEmptyClass(filepath, className, langauge);
}
