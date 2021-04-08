#include "ShaderMetasystem.h"
#include "Runtime/Rendering/Shaders/ShaderReader.h"

void ShaderMetasystem::GenerateMetadata(const std::string& filepath, std::ofstream& outFile)
{
	FShaderDataInternal data = ShaderReader::ParseShader(filepath);

	outFile << "Language: " << ShaderReader::LanguageToString(data.language) << std::endl;
}
