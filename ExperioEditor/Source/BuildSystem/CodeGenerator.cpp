#include "CodeGenerator.h"
#include "../CodeParser/Cpp/CppCodeStream.h"
#include "../Framework/Values.h"

void CodeGenerator::GenerateComponentManager()
{
	CppCodeOStream outFile("DemoProjectComponentManager.h");


}

void CodeGenerator::GenerateTagFile()
{
	CppCodeOStream outFile("DemoProjectTag.cpp");

	outFile << "#include <cstring>" << Debug::endl;
	outFile << "#include <string>" << Debug::endl << Debug::endl;

	outFile << "#ifndef EXPERIO_EDITOR" << Debug::endl;

	outFile << "unsigned short DefaultTagStringToNum(const char* string)" << Debug::endl;
	outFile << "{" << Debug::endl;

	ExperioEditor::GetTags().ForEach([&outFile](const uint16_t& key, const std::string& value) {
		outFile << "if(strcmp(string, \"" << value << "\")) { return " << std::to_string(key) << "; }" << Debug::endl;
	});

	outFile << "	return 0;" << Debug::endl;
	outFile << "}" << Debug::endl;
	
	outFile << "std::string DefaultTagNumToString(unsigned short num)" << Debug::endl;
	outFile << "{" << Debug::endl;
	outFile << "	switch(num)" << Debug::endl;
	outFile << "	{" << Debug::endl;

	ExperioEditor::GetTags().ForEach([&outFile](const uint16_t& key, const std::string& value) {
		outFile << "case " << key << ": " << "return \"" << value << "\";" << Debug::endl;
	});

	outFile << "	}" << Debug::endl;
	outFile << "	return \"Tag\";" << Debug::endl;
	outFile << "}" << Debug::endl;

	outFile << "#endif" << Debug::endl;
}
