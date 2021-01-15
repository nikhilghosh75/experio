#include "LSerializationOperations.h"
#include "../CodeParser/Cpp/LCpp.h"
#include "BinarySaveParams.h"
#include "Runtime/Framework/BinaryParams.h"
#include "Runtime/Framework/Params.h"

#define PB_SERIALIZED_STRING_SIZE 8
#define PB_SERIALIZED_MATERIAL_SIZE 4

std::string LSerializationOperations::BinaryParseFunctionFromType(EParamType type)
{
	switch (type)
	{
	case EParamType::AUDIO: return "BinaryParseAudio";
	case EParamType::BOOL: return "BinaryParseBool";
	case EParamType::BOX: return "BinaryParseBox";
	case EParamType::BYTE: return "BinaryParseByte";
	case EParamType::COLOR: return "BinaryParseColor";
	case EParamType::CURVE: return "BinaryParseCurve";
	case EParamType::DATA: return "BinaryParseData";
	case EParamType::DOUBLE: return "BinaryParseDouble";
	case EParamType::FILE: return "BinaryParseFile";
	case EParamType::FLOAT: return "BinaryParseFloat";
	case EParamType::FONT: return "BinaryParseFont";
	case EParamType::INT: return "BinaryParseInt";
	case EParamType::LONG: return "BinaryParseLongLong";
	case EParamType::MATERIAL: return "BinaryParseMaterial";
	case EParamType::MESH: return "BinaryParseMesh";
	case EParamType::QUATERNION: return "BinaryParseQuaternion";
	case EParamType::RECT: return "BinaryParseRect";
	case EParamType::SHADER: return "BinaryParseShader";
	case EParamType::SHORT: return "BinaryParseShort";
	case EParamType::SPHERICALPOINT: return "BinaryParseSphericalPoint";
	case EParamType::TEXTURE: return "BinaryParseTexture";
	case EParamType::UBYTE: return "BinaryParseUByte";
	case EParamType::UINT: return "BinaryParseUInt";
	case EParamType::ULONG: return "BinaryParseULong";
	case EParamType::USHORT: return "BinaryParseUShort";
	case EParamType::VECTOR2: return "BinaryParseVector2";
	case EParamType::VECTOR3: return "BinaryParseVector3";
	case EParamType::VECTOR4: return "BinaryParseVector4";
	case EParamType::VIDEO: return "BinaryParseVideo";
	}
	return "";
}

std::string LSerializationOperations::BinarySaveFunctionFromType(EParamType type)
{
	switch (type)
	{
	case EParamType::AUDIO: return "BinarySaveAudio";
	case EParamType::BOOL: return "BinarySaveBool";
	case EParamType::BOX: return "BinarySaveBox";
	case EParamType::BYTE: return "BinarySaveByte";
	case EParamType::COLOR: return "BinarySaveColor";
	case EParamType::CURVE: return "BinarySaveCurve";
	case EParamType::DATA: return "BinarySaveData";
	case EParamType::DOUBLE: return "BinarySaveDouble";
	case EParamType::FILE: return "BinarySaveFile";
	case EParamType::FLOAT: return "BinarySaveFloat";
	case EParamType::FONT: return "BinarySaveFont";
	case EParamType::INT: return "BinarySaveInt";
	case EParamType::LONG: return "BinarySaveLongLong";
	case EParamType::MATERIAL: return "BinarySaveMaterial";
	case EParamType::MESH: return "BinarySaveMesh";
	case EParamType::QUATERNION: return "BinarySaveQuaternion";
	case EParamType::RECT: return "BinarySaveRect";
	case EParamType::SHADER: return "BinarySaveShader";
	case EParamType::SHORT: return "BinarySaveShort";
	case EParamType::SPHERICALPOINT: return "BinarySaveSphericalPoint";
	case EParamType::TEXTURE: return "BinarySaveTexture";
	case EParamType::UBYTE: return "BinarySaveUByte";
	case EParamType::UINT: return "BinarySaveUInt";
	case EParamType::ULONG: return "BinarySaveULong";
	case EParamType::USHORT: return "BinarySaveUShort";
	case EParamType::VECTOR2: return "BinarySaveVector2";
	case EParamType::VECTOR3: return "BinarySaveVector3";
	case EParamType::VECTOR4: return "BinarySaveVector4";
	case EParamType::VIDEO: return "BinarySaveVideo";
	}
	return "";
}

std::string LSerializationOperations::CastString(const std::string & type, EParamType paramType)
{
	if (!LCpp::IsIntegerType(type) && IsIntegerParamType(paramType)) return "(" + type + ")";

	if(type.find("Material*") != std::string::npos) return "(" + type + ")";

	return "";
}

#define PB_CONVERT_PARAM(_varName_, _parseFunc_, _saveFunc_) \
	auto _varName_ = _parseFunc_(paramData);\
	_saveFunc_(_varName_, outFile);

void LSerializationOperations::ConvertToBinary(const std::vector<std::string>& params, CodeClass & codeClass, const CodeProject& project, std::ofstream & outFile)
{
	int currentParam = 0;
	for (int i = 0; i < codeClass.params.size(); i++)
	{
		CodeParam& param = codeClass.params[i];
		
		if (param.accessType != ECodeAccessType::Private) continue;
		std::string paramData = params[currentParam].substr(params[currentParam].find(':') + 1);

		EParamType paramType = TypenameToParamType(param.name, project).value();
		
		switch (paramType)
		{
		case EParamType::AUDIO: { PB_CONVERT_PARAM(audioClip, ParseAudio, BinarySaveAudio); break; }
		case EParamType::BOOL: { PB_CONVERT_PARAM(tempBool, ParseBool, BinarySaveBool); break; }
		case EParamType::BOX: { PB_CONVERT_PARAM(box, ParseBox, BinarySaveBox); break; }
		case EParamType::BYTE: { PB_CONVERT_PARAM(tempByte, ParseByte, BinarySaveByte); break; }
		case EParamType::COLOR: { PB_CONVERT_PARAM(color, ParseColor, BinarySaveColor); break; }
		case EParamType::CURVE: { PB_CONVERT_PARAM(curve, ParseCurve, BinarySaveCurve); break; }
		case EParamType::DATA: { PB_CONVERT_PARAM(datatable, ParseData, BinarySaveData); break; }
		case EParamType::DOUBLE: { PB_CONVERT_PARAM(tempDouble, ParseDouble, BinarySaveDouble); break; }
		case EParamType::FILE: { PB_CONVERT_PARAM(file, ParseFile, BinarySaveFile); break; }
		case EParamType::FLOAT: { PB_CONVERT_PARAM(tempFloat, ParseFloat, BinarySaveFloat); break; }
		case EParamType::FONT: { PB_CONVERT_PARAM(font, ParseFont, BinarySaveFont); break; }
		case EParamType::INT: { PB_CONVERT_PARAM(tempInt, ParseInt, BinarySaveInt); break; }
		case EParamType::LONG: { PB_CONVERT_PARAM(tempLong, ParseLongLong, BinarySaveLongLong); break; }
		case EParamType::MATERIAL: { PB_CONVERT_PARAM(material, ParseMaterial, BinarySaveMaterial); break; }
		case EParamType::MESH: { PB_CONVERT_PARAM(mesh, ParseMesh, BinarySaveMesh); break; }
		case EParamType::QUATERNION: { PB_CONVERT_PARAM(quat, ParseQuaternion, BinarySaveQuaternion); break; }
		case EParamType::RECT: { PB_CONVERT_PARAM(rect, ParseRect, BinarySaveRect); break; }
		// case EParamType::SHADER: { PB_CONVERT_PARAM(shader, ParseShader, BinarySaveShader); break; }
		case EParamType::SHORT: { PB_CONVERT_PARAM(tempShort, ParseShort, BinarySaveShort); break; }
		case EParamType::SPHERICALPOINT: { PB_CONVERT_PARAM(sphere, ParseSphericalPoint, BinarySaveSphericalPoint); break; }
		case EParamType::TEXTURE: { PB_CONVERT_PARAM(texture, ParseTexture, BinarySaveTexture); break; }
		case EParamType::UBYTE: { PB_CONVERT_PARAM(tempUByte, ParseUByte, BinarySaveUByte); break; }
		case EParamType::UINT: { PB_CONVERT_PARAM(tempUInt, ParseUInt, BinarySaveUInt); break; }
		case EParamType::ULONG: { PB_CONVERT_PARAM(tempULong, ParseULongLong, BinarySaveLongLong); break; }
		case EParamType::USHORT: { PB_CONVERT_PARAM(tempUShort, ParseUShort, BinarySaveUShort); break; }
		case EParamType::VECTOR2: { PB_CONVERT_PARAM(v2, ParseVector2, BinarySaveVector2); break; }
		case EParamType::VECTOR3: { PB_CONVERT_PARAM(v3, ParseVector3, BinarySaveVector3); break; }
		case EParamType::VECTOR4: { PB_CONVERT_PARAM(v4, ParseVector4, BinarySaveVector4); break; }
		}

		currentParam++;
	}
}

EParamType LSerializationOperations::EnumDataTypeToParamType(EEnumDataType dataType)
{
	switch (dataType)
	{
	case EEnumDataType::BYTE: return EParamType::BYTE;
	case EEnumDataType::INT: return EParamType::INT;
	case EEnumDataType::LONGLONG: return EParamType::LONG;
	case EEnumDataType::SHORT: return EParamType::SHORT;
	case EEnumDataType::UBYTE: return EParamType::UBYTE;
	case EEnumDataType::UINT: return EParamType::UINT;
	case EEnumDataType::ULONGLONG: return EParamType::ULONG;
	case EEnumDataType::USHORT: return EParamType::USHORT;
	}
	return EParamType::ULONG;
}

void LSerializationOperations::GenerateBinarySerializer(const CodeClass & codeClass, const CodeProject & codeProject, 
	CppCodeOStream& os)
{
	for (uint32_t i = 0; i < codeClass.params.size(); i++)
	{
		if (codeClass.params[i].accessType != ECodeAccessType::Public) continue;

		std::optional<EParamType> paramType = TypenameToParamType(codeClass.params[i].type, codeProject);
		if (paramType)
		{
			os << BinarySaveFunctionFromType(paramType.value()) << "(component->" << codeClass.params[i].name
				<< ", stream);" << Debug::endl;
		}
	}
}

void LSerializationOperations::GenerateBinaryParser(const CodeClass & codeClass, const CodeProject & codeProject, 
	CppCodeOStream& os)
{
	size_t currentOffset = 0;
	for (uint32_t i = 0; i < codeClass.params.size(); i++)
	{
		if (codeClass.params[i].accessType != ECodeAccessType::Public) continue;

		std::optional<EParamType> paramType = TypenameToParamType(codeClass.params[i].type, codeProject);
		if (paramType)
		{
			os << "component->" << codeClass.params[i].name << " = " << CastString(codeClass.params[i].type, paramType.value())
				<< BinaryParseFunctionFromType(paramType.value()) << "((void*)((char*)data + " << std::to_string(currentOffset) 
				<< "));" << Debug::endl;
			currentOffset += SizeOfBinaryParam(paramType.value());
		}
	}
}

void LSerializationOperations::GenerateParser(const CodeClass & codeClass, const CodeProject & codeProject, 
	CppCodeOStream& os)
{
	size_t paramOffset = 0;
	for (uint32_t i = 0; i < codeClass.params.size(); i++)
	{
		if (codeClass.params[i].accessType != ECodeAccessType::Public) continue;

		std::optional<EParamType> paramType = TypenameToParamType(codeClass.params[i].type, codeProject);
		if (paramType)
		{
			os << "component->" << codeClass.params[i].name << " = " << CastString(codeClass.params[i].type, paramType.value())
				<< ParseFunctionFromType(paramType.value()) << "(params[" << std::to_string(paramOffset) << "]);" << Debug::endl;
			paramOffset++;
		}
	}
}

void LSerializationOperations::GenerateSerializer(const CodeClass & codeClass, const CodeProject & codeProject, CppCodeOStream& os)
{
	for (uint32_t i = 0; i < codeClass.params.size(); i++)
	{
		if (codeClass.params[i].accessType != ECodeAccessType::Public) continue;

		std::optional<EParamType> paramType = TypenameToParamType(codeClass.params[i].type, codeProject);
		if (paramType)
		{
			os << "PB_SAVE_PARAM(\"" << codeClass.params[i].name << "\", component->" << codeClass.params[i].name
				<< ", " << SaveFunctionFromType(paramType.value()) << ");" << Debug::endl;
		}
	}
}

bool LSerializationOperations::IsIntegerParamType(EParamType paramType)
{
	return paramType == EParamType::BYTE || paramType == EParamType::INT || paramType == EParamType::LONG
		|| paramType == EParamType::SHORT || paramType == EParamType::UBYTE || paramType == EParamType::UINT
		|| paramType == EParamType::ULONG || paramType == EParamType::USHORT;
}

std::string LSerializationOperations::ParseFunctionFromType(EParamType type)
{
	switch (type)
	{
	case EParamType::AUDIO: return "ParseAudio";
	case EParamType::BOOL: return "ParseBool";
	case EParamType::BOX: return "ParseBox";
	case EParamType::BYTE: return "ParseByte";
	case EParamType::COLOR: return "ParseColor";
	case EParamType::CURVE: return "ParseCurve";
	case EParamType::DATA: return "ParseData";
	case EParamType::DOUBLE: return "ParseDouble";
	case EParamType::FILE: return "ParseFile";
	case EParamType::FLOAT: return "ParseFloat";
	case EParamType::FONT: return "ParseFont";
	case EParamType::INT: return "ParseInt";
	case EParamType::LONG: return "ParseLongLong";
	case EParamType::MATERIAL: return "ParseMaterial";
	case EParamType::MESH: return "ParseMesh";
	case EParamType::QUATERNION: return "ParseQuaternion";
	case EParamType::RECT: return "ParseRect";
	case EParamType::SHADER: return "ParseShader";
	case EParamType::SHORT: return "ParseShort";
	case EParamType::SPHERICALPOINT: return "ParseSphericalPoint";
	case EParamType::TEXTURE: return "ParseTexture";
	case EParamType::UBYTE: return "ParseUByte";
	case EParamType::UINT: return "ParseUInt";
	case EParamType::ULONG: return "ParseULong";
	case EParamType::USHORT: return "ParseUShort";
	case EParamType::VECTOR2: return "ParseVector2";
	case EParamType::VECTOR3: return "ParseVector3";
	case EParamType::VECTOR4: return "ParseVector4";
	case EParamType::VIDEO: return "ParseVideo";
	}
	return "";
}

size_t LSerializationOperations::SerializedSizeOf(const CodeClass & codeClass, const CodeProject& codeProject, ECodingLanguage language)
{
	const std::vector<CodeParam> params = codeClass.params;
	size_t size = 0;
	for (size_t i = 0; i < params.size(); i++)
	{
		if (params[i].accessType != ECodeAccessType::Public) continue;

		size += SizeOfParam(params[i], codeProject, language);
	}
	return size;
}

size_t LSerializationOperations::SizeOfDefaultType(const std::string & name, ECodingLanguage language)
{
	switch (language)
	{
	case ECodingLanguage::CPlusPlus:
		return LCpp::SizeOfDefeaultType(name);
	case ECodingLanguage::CSharp:
		if (name == "bool") return 1;
		if (name == "byte") return 1;
		if (name == "char") return 1;
		if (name == "decimal") return 4;
		if (name == "float") return 4;
		if (name == "int") return 4;
		if (name == "long") return 8;
		if (name == "uint") return 4;
		if (name == "ulong") return 8;
		break;
	}
	return 0;
}

size_t LSerializationOperations::SizeOfParam(const CodeParam& param, const CodeProject & codeProject, ECodingLanguage language)
{
	const std::string& paramTypename = param.type;

	// Search for Default Types
	size_t foundSize = SizeOfDefaultType(paramTypename, language);
	if (foundSize != 0)
	{
		return foundSize;
	}
	if (LCodeParser::IsString(param.type, language))
	{
		return PB_SERIALIZED_STRING_SIZE;
	}

	if (paramTypename.find("Material*") != std::string::npos)
	{
		return PB_SERIALIZED_MATERIAL_SIZE;
	}

	// Search for Experio Types that can be serialized
	foundSize = SizeOfExperioSerializedType(paramTypename);
	if (foundSize != 0)
	{
		return foundSize;
	}

	// Search for types in dependencies that can be serialized
	foundSize = SizeOfGLMSerializedType(paramTypename);
	if (foundSize != 0)
	{
		return foundSize;
	}

	// Search for Enums
	for (size_t i = 0; i < codeProject.enums.size(); i++)
	{
		if (codeProject.enums[i].name == paramTypename)
		{
			return SizeOfEnum(codeProject.enums[i]);
		}
	}

	return 0;
}

size_t LSerializationOperations::SizeOfEnum(const CodeEnum & codeEnum)
{
	return SizeOfEnum(codeEnum.dataType);
}

size_t LSerializationOperations::SizeOfEnum(EEnumDataType dataType)
{
	switch (dataType)
	{
	case EEnumDataType::BYTE: return 1;
	case EEnumDataType::UBYTE: return 1;
	case EEnumDataType::SHORT: return 2;
	case EEnumDataType::USHORT: return 2;
	case EEnumDataType::INT: return 4;
	case EEnumDataType::UINT: return 4;
	case EEnumDataType::LONGLONG: return 8;
	case EEnumDataType::ULONGLONG: return 8;
	}
	return 0;
}

size_t LSerializationOperations::SizeOfExperioSerializedType(const std::string & name)
{
	if (name == "FVector2") return 8;
	if (name == "FVector3") return 12;
	if (name == "FVector4") return 16;
	if (name == "FCurve") return 0;
	if (name == "MeshRef") return 4;
	if (name == "FQuaternion") return 16;
	if (name == "FRect") return 16;
	if (name == "Shader") return 4;
	if (name == "FSphericalPoint") return 12;
	if (name == "TextureRef") return 4;
	if (name == "Datatable") return 4;
	return 0;
}

size_t LSerializationOperations::SizeOfGLMSerializedType(const std::string & name)
{
	if (name == "glm::mat4") return 64;
	if (name == "glm::mat3") return 36;
	if (name == "glm::mat2") return 16;
	// Add other types here
	return 0;
}

std::string LSerializationOperations::SaveFunctionFromType(EParamType type)
{
	switch (type)
	{
	case EParamType::AUDIO: return "SaveAudio";
	case EParamType::BOOL: return "SaveBool";
	case EParamType::BOX: return "SaveBox";
	case EParamType::BYTE: return "SaveByte";
	case EParamType::COLOR: return "SaveColor";
	case EParamType::CURVE: return "SaveCurve";
	case EParamType::DATA: return "SaveData";
	case EParamType::DOUBLE: return "SaveDouble";
	case EParamType::FILE: return "SaveFile";
	case EParamType::FLOAT: return "SaveFloat";
	case EParamType::FONT: return "SaveFont";
	case EParamType::INT: return "SaveInt";
	case EParamType::LONG: return "SaveLongLong";
	case EParamType::MATERIAL: return "SaveMaterial";
	case EParamType::MESH: return "SaveMesh";
	case EParamType::QUATERNION: return "SaveQuaternion";
	case EParamType::RECT: return "SaveRect";
	case EParamType::SHADER: return "SaveShader";
	case EParamType::SHORT: return "SaveShort";
	case EParamType::SPHERICALPOINT: return "SaveSphericalPoint";
	case EParamType::TEXTURE: return "SaveTexture";
	case EParamType::UBYTE: return "SaveUByte";
	case EParamType::UINT: return "SaveUInt";
	case EParamType::ULONG: return "SaveULong";
	case EParamType::USHORT: return "SaveUShort";
	case EParamType::VECTOR2: return "SaveVector2";
	case EParamType::VECTOR3: return "SaveVector3";
	case EParamType::VECTOR4: return "SaveVector4";
	case EParamType::VIDEO: return "SaveVideo";
	}
	return "";
}

std::optional<EParamType> LSerializationOperations::TypenameToParamType(const std::string & name, const CodeProject& project)
{
	if (name == "AudioRef") return EParamType::AUDIO;
	if (name == "bool") return EParamType::BOOL;
	if (name == "FBox") return EParamType::BOX;
	if (name == "byte") return EParamType::BYTE;
	if (name == "int8_t") return EParamType::BYTE;
	if (name == "FColor") return EParamType::COLOR;
	if (name == "FCurve") return EParamType::CURVE;
	if (name == "DatatableRef") return EParamType::DATA;
	if (name == "double") return EParamType::DOUBLE;
	if (name == "FileRef") return EParamType::FILE;
	if (name == "float") return EParamType::FLOAT;
	if (name == "int") return EParamType::INT;
	if (name == "int32_t") return EParamType::INT;
	if (name == "long") return EParamType::LONG;
	if (name == "long long") return EParamType::LONG;
	if (name == "int64_t") return EParamType::LONG;
	if (name == "MeshRef") return EParamType::MESH;
	if (name == "FQuaternion") return EParamType::QUATERNION;
	if (name == "FRect") return EParamType::RECT;
	if (name == "Shader*") return EParamType::SHADER;
	if (name == "short") return EParamType::SHORT;
	if (name == "int16_t") return EParamType::SHORT;
	if (name == "FSphericalPoint") return EParamType::SPHERICALPOINT;
	if (name == "TextureRef") return EParamType::TEXTURE;
	if (name == "unsigned char") return EParamType::UBYTE;
	if (name == "uint8_t") return EParamType::UBYTE;
	if (name == "unsigned int") return EParamType::UINT;
	if (name == "uint32_t") return EParamType::UINT;
	if (name == "unsigned long long") return EParamType::ULONG;
	if (name == "uint64_t") return EParamType::ULONG;
	if (name == "unsigned short") return EParamType::USHORT;
	if (name == "uint16_t") return EParamType::USHORT;
	if (name == "FVector2") return EParamType::VECTOR2;
	if (name == "FVector3") return EParamType::VECTOR3;
	if (name == "FVector4") return EParamType::VECTOR4;
	if (name == "VideoRef") return EParamType::VIDEO;

	uint32_t enumIndex = project.FindIndexOfEnum(name);
	if (enumIndex != CODE_OBJECT_NOT_FOUND)
	{
		return EnumDataTypeToParamType(project.enums[enumIndex].dataType);
	}

	if (name.find("Material*") != std::string::npos)
	{
		return EParamType::MATERIAL;
	}

	return {};
}
