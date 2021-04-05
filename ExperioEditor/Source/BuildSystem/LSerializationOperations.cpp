#include "LSerializationOperations.h"
#include "../CodeParser/Cpp/LCpp.h"
#include "../Framework/EditorProject.h"
#include "BinarySaveParams.h"
#include "Runtime/Framework/BinaryParams.h"
#include "Runtime/Framework/Component.h"
#include "Runtime/Framework/Params.h"
#include "Runtime/Math/Frustum.h"
#include "Runtime/Rendering/Materials/BillboardMaterial.h"
#include "Runtime/Rendering/Materials/MeshMaterial.h"

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
	case EParamType::STRING: return "BinaryParseString";
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
		
		if (param.accessType != ECodeAccessType::Public) 
			continue;
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
		case EParamType::STRING: {PB_CONVERT_PARAM(string, ParseString, BinarySaveString); break; }
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

std::vector<FSerializationInfo> LSerializationOperations::GenerateSerializedFields(unsigned int classId, const CodeProject& project)
{
	FComponentInfo componentInfo = EditorProject::componentClasses.Get(classId);
	const CodeClass& codeClass = project.classes[project.FindIndexOfClass(componentInfo.name)];
	std::vector<FSerializationInfo> serializedFields;

	size_t currentOffset = sizeof(Component);
	for (size_t i = 0; i < codeClass.params.size(); i++)
	{
		auto optionalParamType = LSerializationOperations::TypenameToParamType(codeClass.params[i].type, project);

		// If can't figure out type, ignore it
		if (!optionalParamType)
		{
			continue;
		}

		size_t paramSize = LSerializationOperations::SizeOfParam(codeClass.params[i], project, ECodingLanguage::CPlusPlus);
		bool isDefault = LCpp::IsIntegerType(codeClass.params[i].type) || LCpp::IsPointer(codeClass.params[i].type);
		currentOffset = LCpp::AlignForward(currentOffset, paramSize, isDefault);
		currentOffset += paramSize;

		if (codeClass.params[i].accessType != ECodeAccessType::Public) continue;

		FSerializationInfo& info = serializedFields.emplace_back();
		info.type = optionalParamType.value();
		info.typeName = codeClass.params[i].type;
		info.offset = currentOffset - paramSize;
		info.name = codeClass.params[i].name;
	}

	return serializedFields;
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
	case EParamType::STRING: return "ParseString";
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

void LSerializationOperations::SaveToBinary(void * component, unsigned int componentId, const CodeProject & project, std::ofstream & outFile)
{
	FComponentInfo componentInfo = EditorProject::componentClasses.Get(componentId);
	const CodeClass& codeClass = project.classes[project.FindIndexOfClass(componentInfo.name)];

	std::vector<FSerializationInfo> serializedFields = LSerializationOperations::GenerateSerializedFields(componentId, project);
	for (size_t i = 0; i < serializedFields.size(); i++)
	{
		outFile << "\t\t\t" << serializedFields[i].name << ": ";
		SaveParamToText(component, serializedFields[i], outFile);
		outFile << std::endl;
	}
}

#define PB_SAVE_PARAM(_typename_, _funcname_) _funcname_(*( _typename_*)((char*)component + serializedField.offset), outFile)

void LSerializationOperations::SaveParamToBinary(void * component, FSerializationInfo & serializedField, std::ofstream & outFile)
{
	switch (serializedField.type)
	{
	case EParamType::AUDIO: PB_SAVE_PARAM(FAudioClip, BinarySaveAudio); break;
	case EParamType::BOOL: PB_SAVE_PARAM(bool, BinarySaveBool); break;
	case EParamType::BOX: PB_SAVE_PARAM(FBox, BinarySaveBox); break;
	case EParamType::BYTE: PB_SAVE_PARAM(int8_t, BinarySaveByte); break;
	case EParamType::COLOR: PB_SAVE_PARAM(FColor, BinarySaveColor); break;
	case EParamType::CURVE: PB_SAVE_PARAM(FCurve, BinarySaveCurve); break;
	case EParamType::DATA: PB_SAVE_PARAM(DataRef, BinarySaveData); break;
	case EParamType::DOUBLE: PB_SAVE_PARAM(double, BinarySaveDouble); break;
	case EParamType::FILE: PB_SAVE_PARAM(FileRef, BinarySaveFile); break;
	case EParamType::FLOAT: PB_SAVE_PARAM(float, BinarySaveFloat); break;
	case EParamType::FONT: PB_SAVE_PARAM(FontRef, BinarySaveFont); break;
	case EParamType::INT: PB_SAVE_PARAM(int, BinarySaveInt); break;
	case EParamType::LONG: PB_SAVE_PARAM(long long, BinarySaveLongLong); break;
	case EParamType::MATERIAL: BinarySaveMaterial((Material*)((char*)component + serializedField.offset), outFile); break;
	case EParamType::MESH: PB_SAVE_PARAM(MeshRef, BinarySaveMesh); break;
	case EParamType::QUATERNION: PB_SAVE_PARAM(FQuaternion, BinarySaveQuaternion); break;
	case EParamType::RECT: PB_SAVE_PARAM(FRect, BinarySaveRect); break;
	case EParamType::SHORT: PB_SAVE_PARAM(short, BinarySaveShort); break;
	case EParamType::SPHERICALPOINT: PB_SAVE_PARAM(FSphericalPoint, BinarySaveSphericalPoint); break;
	case EParamType::STRING: PB_SAVE_PARAM(std::string, BinarySaveString); break;
	case EParamType::TEXTURE: PB_SAVE_PARAM(TextureRef, BinarySaveTexture); break;
	case EParamType::VECTOR2: PB_SAVE_PARAM(FVector2, BinarySaveVector2); break;
	case EParamType::VECTOR3: PB_SAVE_PARAM(FVector3, BinarySaveVector3); break;
	case EParamType::VECTOR4: PB_SAVE_PARAM(FVector4, BinarySaveVector4); break;
	}
}

void LSerializationOperations::SaveToText(void * component, unsigned int componentId, const CodeProject & project, std::ofstream & outFile)
{
	FComponentInfo componentInfo = EditorProject::componentClasses.Get(componentId);
	const CodeClass& codeClass = project.classes[project.FindIndexOfClass(componentInfo.name)];
	
	std::vector<FSerializationInfo> serializedFields = LSerializationOperations::GenerateSerializedFields(componentId, project);
	for (size_t i = 0; i < serializedFields.size(); i++)
	{
		outFile << "\t\t\t" << serializedFields[i].name << ": ";
		SaveParamToText(component, serializedFields[i], outFile);
		outFile << std::endl;
	}
}

void LSerializationOperations::SaveParamToText(void * component, FSerializationInfo & serializedField, std::ofstream & outFile)
{
	switch (serializedField.type)
	{
	case EParamType::AUDIO: PB_SAVE_PARAM(FAudioClip, SaveAudio); break;
	case EParamType::BOOL: PB_SAVE_PARAM(bool, SaveBool); break;
	case EParamType::BOX: PB_SAVE_PARAM(FBox, SaveBox); break;
	case EParamType::BYTE: PB_SAVE_PARAM(int8_t, SaveByte); break;
	case EParamType::COLOR: PB_SAVE_PARAM(FColor, SaveColor); break;
	case EParamType::CURVE: PB_SAVE_PARAM(FCurve, SaveCurve); break;
	case EParamType::DATA: PB_SAVE_PARAM(DataRef, SaveData); break;
	case EParamType::DOUBLE: PB_SAVE_PARAM(double, SaveDouble); break;
	case EParamType::FILE: PB_SAVE_PARAM(FileRef, SaveFile); break;
	case EParamType::FLOAT: PB_SAVE_PARAM(float, SaveFloat); break;
	case EParamType::FONT: PB_SAVE_PARAM(FontRef, SaveFont); break;
	case EParamType::INT: PB_SAVE_PARAM(int, SaveInt); break;
	case EParamType::LONG: PB_SAVE_PARAM(long long, SaveLongLong); break;
	case EParamType::MATERIAL: SaveMaterial((Material*)((char*)component + serializedField.offset), outFile); break;
	case EParamType::MESH: PB_SAVE_PARAM(MeshRef, SaveMesh); break;
	case EParamType::QUATERNION: PB_SAVE_PARAM(FQuaternion, SaveQuaternion); break;
	case EParamType::RECT: PB_SAVE_PARAM(FRect, SaveRect); break;
	case EParamType::SHORT: PB_SAVE_PARAM(short, SaveShort); break;
	case EParamType::SPHERICALPOINT: PB_SAVE_PARAM(FSphericalPoint, SaveSphericalPoint); break;
	case EParamType::STRING: PB_SAVE_PARAM(std::string, SaveString); break;
	case EParamType::TEXTURE: PB_SAVE_PARAM(TextureRef, SaveTexture); break;
	case EParamType::UBYTE: PB_SAVE_PARAM(uint8_t, SaveUByte); break;
	case EParamType::UINT: PB_SAVE_PARAM(unsigned int, SaveUInt); break;
	case EParamType::ULONG: PB_SAVE_PARAM(unsigned long long, SaveULongLong); break;
	case EParamType::USHORT: PB_SAVE_PARAM(uint16_t, SaveUShort); break;
	case EParamType::VECTOR2: PB_SAVE_PARAM(FVector2, SaveVector2); break;
	case EParamType::VECTOR3: PB_SAVE_PARAM(FVector3, SaveVector3); break;
	case EParamType::VECTOR4: PB_SAVE_PARAM(FVector4, SaveVector4); break;
	}
}

size_t LSerializationOperations::SizeOf(const CodeClass& codeClass, const CodeProject& codeProject, ECodingLanguage language)
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

size_t LSerializationOperations::SizeOfDefaultType(const std::string& name, ECodingLanguage language)
{
	return SerializedSizeOfDefaultType(name, language);
}

size_t LSerializationOperations::SizeOfParam(const CodeParam& param, const CodeProject& codeProject, ECodingLanguage language)
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
		return sizeof(std::string);
	}

	if (LCpp::IsPointer(paramTypename))
	{
		return sizeof(void*);
	}

	if (paramTypename.find("Material*") != std::string::npos)
	{
		return SizeOfMaterial(paramTypename);
	}

	// Search for Experio Types that can be serialized
	foundSize = SizeOfExperioType(paramTypename);
	if (foundSize != 0)
	{
		return foundSize;
	}

	// Search for types in dependencies that can be serialized
	foundSize = SizeOfGLMType(paramTypename);
	if (foundSize != 0)
	{
		return foundSize;
	}

	// Search for Enums
	for (size_t i = 0; i < codeProject.enums.size(); i++)
	{
		if (codeProject.enums[i].name == paramTypename)
		{
			return SerializedSizeOfEnum(codeProject.enums[i]);
		}
	}

	return 0;
}

size_t LSerializationOperations::SizeOfExperioType(const std::string& name)
{
	if (name == "FVector2") return sizeof(FVector2);
	if (name == "FVector3") return sizeof(FVector3);
	if (name == "FVector4") return sizeof(FVector4);
	if (name == "FCurve") return sizeof(FCurve);
	if (name == "MeshRef") return sizeof(MeshRef);
	if (name == "FQuaternion") return sizeof(FQuaternion);
	if (name == "FRect") return sizeof(FRect);
	if (name == "Shader") return sizeof(Shader);
	if (name == "FSphericalPoint") return sizeof(FSphericalPoint);
	if (name == "TextureRef") return sizeof(TextureRef);
	if (name == "DataRef") return sizeof(DataRef);
	if (name == "FileRef") return sizeof(FileRef);
	return 0;
}

size_t LSerializationOperations::SizeOfMaterial(const std::string & name)
{
	if (name == "MeshMaterial") return sizeof(MeshMaterial);
	if (name == "BillboardMaterial") return sizeof(BillboardMaterial);
	return sizeof(Material);
}

size_t LSerializationOperations::SizeOfGLMType(const std::string& name)
{
	if (name == "glm::mat4") return sizeof(glm::mat4);
	if (name == "glm::mat3") return sizeof(glm::mat3);
	if (name == "glm::mat2") return sizeof(glm::mat2);
	if (name == "Frustum") return sizeof(Frustum);
	// Add other types here
	return 0;
}

size_t LSerializationOperations::SerializedSizeOf(const CodeClass & codeClass, const CodeProject& codeProject, ECodingLanguage language)
{
	const std::vector<CodeParam> params = codeClass.params;
	size_t size = 0;
	for (size_t i = 0; i < params.size(); i++)
	{
		if (params[i].accessType != ECodeAccessType::Public) continue;

		size += SerializedSizeOfParam(params[i], codeProject, language);
	}
	return size;
}

size_t LSerializationOperations::SerializedSizeOfDefaultType(const std::string & name, ECodingLanguage language)
{
	switch (language)
	{
	case ECodingLanguage::CPlusPlus:
		return LCpp::SizeOfDefaultType(name);
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

size_t LSerializationOperations::SerializedSizeOfParam(const CodeParam& param, const CodeProject & codeProject, ECodingLanguage language)
{
	const std::string& paramTypename = param.type;

	// Search for Default Types
	size_t foundSize = SerializedSizeOfDefaultType(paramTypename, language);
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
	foundSize = SerializedSizeOfExperioType(paramTypename);
	if (foundSize != 0)
	{
		return foundSize;
	}

	// Search for types in dependencies that can be serialized
	foundSize = SerializedSizeOfGLMType(paramTypename);
	if (foundSize != 0)
	{
		return foundSize;
	}

	// Search for Enums
	for (size_t i = 0; i < codeProject.enums.size(); i++)
	{
		if (codeProject.enums[i].name == paramTypename)
		{
			return SerializedSizeOfEnum(codeProject.enums[i]);
		}
	}

	return 0;
}

size_t LSerializationOperations::SerializedSizeOfEnum(const CodeEnum & codeEnum)
{
	return SerializedSizeOfEnum(codeEnum.dataType);
}

size_t LSerializationOperations::SerializedSizeOfEnum(EEnumDataType dataType)
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

size_t LSerializationOperations::SerializedSizeOfExperioType(const std::string & name)
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
	if (name == "FileRef") return 4;
	return 0;
}

size_t LSerializationOperations::SerializedSizeOfGLMType(const std::string & name)
{
	if (name == "glm::mat4") return 64;
	if (name == "glm::mat3") return 36;
	if (name == "glm::mat2") return 16;
	if (name == "Frustum") return 96;
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
	if (name == "FontRef") return EParamType::FONT;
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
	if (name == "std::string") return EParamType::STRING;
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
