#pragma once

#include "Params.h"

bool BinaryParseBool(void* data);
int8_t BinaryParseByte(void* data);
uint8_t BinaryParseUByte(void* data);
int16_t BinaryParseShort(void* data);
uint16_t BinaryParseUShort(void* data);
float BinaryParseFloat(void* data);
int BinaryParseInt(void* data);
unsigned int BinaryParseUInt(void* data);
double BinaryParseDouble(void* data);
long long BinaryParseLongLong(void* data);
unsigned long long BinaryParseULongLong(void* data);

FVector2 BinaryParseVector2(void* data);
FVector3 BinaryParseVector3(void* data);
FVector4 BinaryParseVector4(void* data);
FColor BinaryParseColor(void* data);
FQuaternion BinaryParseQuaternion(void* data);
FRect BinaryParseRect(void* data);
FBox BinaryParseBox(void* data);
FCurve BinaryParseCurve(void* data);
FSphericalPoint BinaryParseSphericalPoint(void* data);

FAudioClip BinaryParseAudio(void* data);
DataRef BinaryParseData(void* data);
FileRef BinaryParseFile(void* data);
FontRef BinaryParseFont(void* data);
Material* BinaryParseMaterial(void* data);
MeshRef BinaryParseMesh(void* data);
Shader* BinaryParseShader(void* data);
TextureRef BinaryParseTexture(void* data);

size_t SizeOfBinaryParam(EParamType type);