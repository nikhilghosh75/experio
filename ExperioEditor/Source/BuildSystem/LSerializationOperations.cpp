#include "LSerializationOperations.h"

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
	case EParamType::FLOAT: return "BinaryParseFloat";
	case EParamType::FONT: return "BinaryParseFont";
	case EParamType::INT: return "BinaryParseInt";
	case EParamType::LONG: return "BinaryParseLongLong";
	case EParamType::MESH: return "BinaryParseMesh";
	case EParamType::QUATERNION: return "BinaryParseQuaternion";
	case EParamType::RECT: return "BinaryParseRect";
	case EParamType::SHADER: return "BinaryParseShader";
	case EParamType::SHORT: return "BinaryParseShort";
	case EParamType::SPHERICALPOINT: return "BinaryParseSphericalPoint";
	case EParamType::TEXTURE: return "BinaryParseTexture";
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
	case EParamType::FLOAT: return "BinarySaveFloat";
	case EParamType::FONT: return "BinarySaveFont";
	case EParamType::INT: return "BinarySaveInt";
	case EParamType::LONG: return "BinarySaveLongLong";
	case EParamType::MESH: return "BinarySaveMesh";
	case EParamType::QUATERNION: return "BinarySaveQuaternion";
	case EParamType::RECT: return "BinarySaveRect";
	case EParamType::SHADER: return "BinarySaveShader";
	case EParamType::SHORT: return "BinarySaveShort";
	case EParamType::SPHERICALPOINT: return "BinarySaveSphericalPoint";
	case EParamType::TEXTURE: return "BinarySaveTexture";
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
	case EParamType::FLOAT: return "ParseFloat";
	case EParamType::FONT: return "ParseFont";
	case EParamType::INT: return "ParseInt";
	case EParamType::LONG: return "ParseLongLong";
	case EParamType::MESH: return "ParseMesh";
	case EParamType::QUATERNION: return "ParseQuaternion";
	case EParamType::RECT: return "ParseRect";
	case EParamType::SHADER: return "ParseShader";
	case EParamType::SHORT: return "ParseShort";
	case EParamType::SPHERICALPOINT: return "ParseSphericalPoint";
	case EParamType::TEXTURE: return "ParseTexture";
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
	case EParamType::FLOAT: return "SaveFloat";
	case EParamType::FONT: return "SaveFont";
	case EParamType::INT: return "SaveInt";
	case EParamType::LONG: return "SaveLongLong";
	case EParamType::MESH: return "SaveMesh";
	case EParamType::QUATERNION: return "SaveQuaternion";
	case EParamType::RECT: return "SaveRect";
	case EParamType::SHADER: return "SaveShader";
	case EParamType::SHORT: return "SaveShort";
	case EParamType::SPHERICALPOINT: return "SaveSphericalPoint";
	case EParamType::TEXTURE: return "SaveTexture";
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
