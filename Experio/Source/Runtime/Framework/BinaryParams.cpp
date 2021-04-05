#include "BinaryParams.h"
#include "Project.h"
#include "AssetMap.h"
#include "../Files/Data/DataReader.h"

bool BinaryParseBool(void * data)
{
	return *(uint8_t*)data != 0;
}

int8_t BinaryParseByte(void * data)
{
	return *(int8_t*)data;
}

uint8_t BinaryParseUByte(void* data)
{
	return *(uint8_t*)data;
}

int16_t BinaryParseShort(void * data)
{
	return *(int16_t*)data;
}

uint16_t BinaryParseUShort(void * data)
{
	return *(uint16_t*)data;
}

float BinaryParseFloat(void * data)
{
	return *(float*)data;
}

int BinaryParseInt(void * data)
{
	return *(int*)data;
}

unsigned int BinaryParseUInt(void * data)
{
	return *(unsigned int*)data;
}

double BinaryParseDouble(void * data)
{
	return *(double*)data;
}

long long BinaryParseLongLong(void * data)
{
	return *(long long*)data;
}

unsigned long long BinaryParseULongLong(void * data)
{
	return *(unsigned long long*)data;
}

std::string BinaryParseString(void* data)
{
	return "NOT IMPLEMENTED";
}

FVector2 BinaryParseVector2(void * data)
{
	return FVector2(*(float*)data, *((float*)(data) + 1));
}

FVector3 BinaryParseVector3(void * data)
{
	return FVector3(*(float*)data, *((float*)(data) + 1), *((float*)data + 2));
}

FVector4 BinaryParseVector4(void * data)
{
	return FVector4(*(float*)data, *((float*)(data)+1), *((float*)data + 2), *((float*)data + 3));
}

FColor BinaryParseColor(void * data)
{
	return FColor(*(float*)data, *((float*)(data)+1), *((float*)data + 2), *((float*)data + 3));
}

FQuaternion BinaryParseQuaternion(void * data)
{
	return FQuaternion(*(float*)data, *((float*)(data)+1), *((float*)data + 2), *((float*)data + 3));
}

FRect BinaryParseRect(void * data)
{
	return FRect(*(float*)data, *((float*)(data)+1), *((float*)data + 2), *((float*)data + 3));
}

FBox BinaryParseBox(void * data)
{
	return FBox(*(float*)data, *((float*)(data)+1), *((float*)data + 2), 
		*((float*)data + 3), *((float*)data + 4), *((float*)data + 5));
}

FCurve BinaryParseCurve(void * data)
{
	Debug::LogError("Function is not complete yet");
	return FCurve();
}

FSphericalPoint BinaryParseSphericalPoint(void * data)
{
	return FSphericalPoint(*(float*)data, *((float*)(data)+1), *((float*)data + 2));
}

FAudioClip BinaryParseAudio(void * data)
{
	Debug::LogError("Function is not complete yet");
	return FAudioClip();
}

DataRef BinaryParseData(void * data)
{
	std::string filepath = AssetMap::assetMap.Get(*(unsigned int*)data);
	return DataManager::LoadData(filepath);
}

FileRef BinaryParseFile(void * data)
{
	return FileRef(*(unsigned int*)data);
}

FontRef BinaryParseFont(void * data)
{
	std::string filepath = AssetMap::assetMap.Get(*(unsigned int*)data);
	return FontManager::LoadFont(filepath);
}

Material * BinaryParseMaterial(void * data)
{
	std::string filepath = AssetMap::assetMap.Get(*(unsigned int*)data);
	return Project::materialManager->LoadMaterialFromFile(filepath);
}

MeshRef BinaryParseMesh(void * data)
{
	std::string filepath = AssetMap::assetMap.Get(*(unsigned int*)data);
	return MeshManager::LoadMesh(filepath);
}

Shader * BinaryParseShader(void * data)
{
	std::string filepath = AssetMap::assetMap.Get(*(unsigned int*)data);
	return ShaderReader::ReadShader(filepath);
}

TextureRef BinaryParseTexture(void * data)
{
	std::string filepath = AssetMap::assetMap.Get(*(unsigned int*)data);
	return TextureManager::LoadTexture(filepath);
}

size_t SizeOfBinaryParam(EParamType type)
{
	switch (type)
	{
	case EParamType::AUDIO: return 0;
	case EParamType::BOOL: return 1;
	case EParamType::BOX: return 24;
	case EParamType::BYTE: return 1;
	case EParamType::COLOR: return 16;
	case EParamType::CURVE: return 0;
	case EParamType::DATA: return 4;
	case EParamType::DOUBLE: return 8;
	case EParamType::FILE: return 4;
	case EParamType::FLOAT: return 4;
	case EParamType::FONT: return 4;
	case EParamType::INT: return 4;
	case EParamType::LONG: return 8;
	case EParamType::MATERIAL: return 4;
	case EParamType::MESH: return 4;
	case EParamType::NARRAY: return 0;
	case EParamType::QUATERNION: return 16;
	case EParamType::RECT: return 16;
	case EParamType::SHADER: return 4;
	case EParamType::SHORT: return 2;
	case EParamType::SPHERICALPOINT: return 12;
	case EParamType::STRING: return 0;
	case EParamType::TEXTURE: return 4;
	case EParamType::UBYTE: return 1;
	case EParamType::UINT: return 4;
	case EParamType::ULONG: return 8;
	case EParamType::USHORT: return 2;
	case EParamType::VECTOR2: return 8;
	case EParamType::VECTOR3: return 12;
	case EParamType::VECTOR4: return 16;
	case EParamType::VIDEO: return 0;
	}
	return 0;
}
