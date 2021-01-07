#pragma once
#include <optional>
#include <string>
#include "../CodeParser/LCodeParser.h"
#include "../CodeParser/Cpp/CppCodeStream.h"
#include "Runtime/Framework/Params.h"

class LSerializationOperations
{
public:
	static std::string BinaryParseFunctionFromType(EParamType type);

	static std::string BinarySaveFunctionFromType(EParamType type);

	static std::string CastString(const std::string& type, EParamType paramType);

	static void ConvertToBinary(const std::vector<std::string>& params, CodeClass& codeClass, const CodeProject& project, std::ofstream& outFile);
	
	static EParamType EnumDataTypeToParamType(EEnumDataType dataType);

	static void GenerateBinarySerializer(const CodeClass& codeClass, const CodeProject& codeProject, CppCodeOStream& os);

	static void GenerateBinaryParser(const CodeClass& codeClass, const CodeProject& codeProject, CppCodeOStream& os);

	static void GenerateParser(const CodeClass& codeClass, const CodeProject& codeProject, CppCodeOStream& os);

	static void GenerateSerializer(const CodeClass& codeClass, const CodeProject& codeProject, CppCodeOStream& os);

	static bool IsIntegerParamType(EParamType paramType);

	static std::string ParseFunctionFromType(EParamType type);

	static std::string SaveFunctionFromType(EParamType type);

	static size_t SerializedSizeOf(const CodeClass& codeClass, const CodeProject& codeProject, ECodingLanguage language);
	static size_t SizeOfDefaultType(const std::string& name, ECodingLanguage language);
	static size_t SizeOfParam(const CodeParam& param, const CodeProject& codeProject, ECodingLanguage language);
	static size_t SizeOfEnum(const CodeEnum& codeEnum);
	static size_t SizeOfEnum(EEnumDataType dataType);
	static size_t SizeOfExperioSerializedType(const std::string& name);
	static size_t SizeOfGLMSerializedType(const std::string& name);

	// Currently works for cpp only
	static std::optional<EParamType> TypenameToParamType(const std::string& name, const CodeProject& project);
};