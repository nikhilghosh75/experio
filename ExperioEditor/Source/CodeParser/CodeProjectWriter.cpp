#include "CodeProjectWriter.h"
#include "LCodeParser.h"

void CodeProjectWriter::WriteToFile(const CodeProject & project, const std::string & filepath)
{
	std::ofstream outFile(filepath);

	outFile << "Language: " << LCodeParser::LanguageToString(project.codingLanguage) << std::endl;
	outFile << "Filepath: " << project.filepath << std::endl;

	outFile << "Classes: [{" << std::endl;
	for (size_t i = 0; i < project.classes.size(); i++)
	{
		WriteClass(project.classes[i], outFile);
		if (i != project.classes.size() - 1)
		{
			outFile << "},{" << std::endl;
		}
	}
	outFile << "}]" << std::endl;

	outFile << "Enums: [{" << std::endl;
	for (size_t i = 0; i < project.enums.size(); i++)
	{
		WriteEnum(project.enums[i], outFile, project.codingLanguage);
		if (i != project.enums.size() - 1)
		{
			outFile << "},{" << std::endl;
		}
	}
	outFile << "}]" << std::endl;

	outFile << "Functions: []";
}

void CodeProjectWriter::WriteClass(const CodeClass & codeClass, std::ofstream& outFile)
{
	outFile << "Name: " << codeClass.name << std::endl;

	outFile << "Filename: " << codeClass.filename << std::endl;

	outFile << "Params: ";
	if (codeClass.params.size() == 0)
		outFile << "[]" << std::endl;
	else
	{
		outFile << "[";
		for (size_t i = 0; i < codeClass.params.size(); i++)
		{
			const CodeParam& param = codeClass.params[i];
			outFile << " \"";

			if (CodeParam::IsStatic(param.keywords))
				outFile << "static ";

			outFile << param.type << " " << param.name << "\" ";

			if (i != codeClass.params.size() - 1)
				outFile << ",";
		}
		outFile << "]" << std::endl;
	}

	outFile << "Functions: ";
	if (codeClass.functions.size() == 0)
	{
		outFile << "[]";
	}
	else
	{
		outFile << "[";
		for (size_t i = 0; i < codeClass.functions.size(); i++)
		{
			const CodeFunction& codeFunction = codeClass.functions[i];
			outFile << " \"" << std::endl;

			if (CodeFunction::IsKeywordStatic(codeFunction.keywords))
				outFile << "static ";

			outFile << codeFunction.returnType << " " << codeFunction.functionName << "(";
			for (size_t i = 0; i < codeFunction.arguments.size(); i++)
			{
				const CodeArg& arg = codeFunction.arguments[i];
				if (arg.isConst)
					outFile << "const ";
				outFile << arg.type << " " << arg.name;

				if (i != codeFunction.arguments.size() - 1)
					outFile << " ,";
			}
			outFile << ")";
			if (i != codeClass.functions.size() - 1)
				outFile << " ,";
		}
		outFile << "]" << std::endl;
	}

	outFile << "InheritsFrom: " << codeClass.inheritance.size();
	for (size_t i = 0; i < codeClass.inheritance.size(); i++)
	{
		outFile << " " << codeClass.inheritance[i];
	}
	outFile << std::endl;
}

void CodeProjectWriter::WriteEnum(const CodeEnum & codeEnum, std::ofstream & outFile, ECodingLanguage language)
{
	outFile << "Name: " << codeEnum.name << std::endl;
	outFile << "Values: [ ";
	codeEnum.values.ForEach([&outFile](const int& key, const std::string& value) {
		outFile << "{" << value << ", " << key << "}, ";
	});
	outFile << "Datatype: " << LCodeParser::EnumDataTypeToString(codeEnum.dataType, language);
}
