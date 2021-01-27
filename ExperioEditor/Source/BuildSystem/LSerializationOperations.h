#pragma once
#include <optional>
#include <string>
#include "../CodeParser/LCodeParser.h"
#include "../CodeParser/Cpp/CppCodeStream.h"
#include "Runtime/Framework/Params.h"
#include "SerializationInfo.h"

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

	static std::vector<FSerializationInfo> GenerateSerializedFields(unsigned int classId, const CodeProject& project);

	static bool IsIntegerParamType(EParamType paramType);

	static std::string ParseFunctionFromType(EParamType type);

	static void SaveToBinary(void* component, unsigned int componentId, const CodeProject& project, std::ofstream& outFile);
	static void SaveParamToBinary(void* component, FSerializationInfo& serializedField, std::ofstream & outFile);

	static void SaveToText(void* component, unsigned int componentId, const CodeProject& project, std::ofstream& outFile);
	static void SaveParamToText(void* component, FSerializationInfo& serializedField, std::ofstream & outFile);

	static std::string SaveFunctionFromType(EParamType type);

	static size_t SizeOf(const CodeClass& codeClass, const CodeProject& codeProject, ECodingLanguage language);
	static size_t SizeOfDefaultType(const std::string& name, ECodingLanguage language);
	static size_t SizeOfParam(const CodeParam& param, const CodeProject& codeProject, ECodingLanguage language);
	static size_t SizeOfExperioType(const std::string& name);
	static size_t SizeOfMaterial(const std::string& name);
	static size_t SizeOfGLMType(const std::string& name);

	static size_t SerializedSizeOf(const CodeClass& codeClass, const CodeProject& codeProject, ECodingLanguage language);
	static size_t SerializedSizeOfDefaultType(const std::string& name, ECodingLanguage language);
	static size_t SerializedSizeOfParam(const CodeParam& param, const CodeProject& codeProject, ECodingLanguage language);
	static size_t SerializedSizeOfEnum(const CodeEnum& codeEnum);
	static size_t SerializedSizeOfEnum(EEnumDataType dataType);
	static size_t SerializedSizeOfExperioType(const std::string& name);
	static size_t SerializedSizeOfGLMType(const std::string& name);

	// Currently works for cpp only
	static std::optional<EParamType> TypenameToParamType(const std::string& name, const CodeProject& project);
};