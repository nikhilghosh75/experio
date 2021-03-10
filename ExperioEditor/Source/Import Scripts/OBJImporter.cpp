#include "ImportScripts.h"
#include "Runtime/Containers/LString.h"
#include "Runtime/Files/LFileOperations.h"
#include <fstream>

void TriangulateFaces(const std::string& filepath)
{
	std::ifstream inFile(filepath);
	std::ofstream outFile(filepath + ".temp");

	bool saveToNewFile = false;

	std::string word;
	while (inFile >> word)
	{
		if (word == "f")
		{
			std::getline(inFile, word);
			size_t numVertices = LString::NumWords(word);

			if (numVertices == 3)
				break;

			saveToNewFile = true;
			std::vector<std::string> vertices = LString::SeperateStringByChar(word, ' ');
			outFile << "f " << vertices[0] << " " << vertices[1] << " " << vertices[2] << std::endl;
			outFile << "f " << vertices[2] << " " << vertices[3] << " " << vertices[0] << std::endl;
		}
		else
		{
			outFile << word;
			std::getline(inFile, word);
			outFile << word << std::endl;
		}
	}

	inFile.close();
	outFile.close();
	if (saveToNewFile)
	{
		std::filesystem::rename(filepath + ".temp", filepath);
	}
	else
	{
		std::filesystem::remove(filepath + ".temp");
	}
}

void GenerateNormals(const std::string& filepath)
{
	std::ifstream inFile(filepath);
	std::ofstream outFile(filepath + ".temp");

	bool saveToNewFile = false;

	std::string word;
	while (inFile >> word)
	{
		if (word == "vn")
		{
			break;
		}
		else if (word == "v")
		{

		}
		else if (word == "f")
		{

		}
		else
		{
			outFile << word;
			std::getline(inFile, word);
			outFile << word << std::endl;
		}
	}

	inFile.close();
	outFile.close();
	if (saveToNewFile)
	{
		std::filesystem::rename(filepath + ".temp", filepath);
	}
	else
	{
		std::filesystem::remove(filepath + ".temp");
	}
}

EImportHandlerResult ImportOBJ(FImportInfo info)
{
	if (!LFileOperations::DoesFileHaveExtension(info.filepath, "obj")) return EImportHandlerResult::NotHandled;

	TriangulateFaces(info.filepath);
	// GenerateNormals(info.filepath);

	return EImportHandlerResult::Handled;
}