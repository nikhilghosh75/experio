#pragma once
#include <string>
#include "../Debug/Debug.h"
#include "../Containers/LString.h"
#include "../Files/LFileOperations.h"

#include "../Audio/AudioClip.h"
#include "../Files/Font/FontReader.h"
#include "../Files/Images/ImageReader.h"
#include "../Files/Mesh/MeshReader.h"
#include "../Math/FVector2.h"
#include "../Math/FVector3.h"
#include "../Math/FVector4.h"
#include "../Math/FQuaternion.h"
#include "../Math/FColor.h"
#include "../Math/FCurve.h"
#include "../Math/Datatable.h"
#include "../Rendering/Materials/Material.h"
#include "../Rendering/Shader.h"

enum class EParamType
{
	BOOL,
	BYTE,
	SHORT,
	USHORT,
	FLOAT,
	INT,
	UINT,
	DOUBLE,
	LONG,
	ULONG,
	VECTOR2,
	VECTOR3,
	VECTOR4,
	COLOR,
	QUATERNION,
	CURVE,
	AUDIO,
	DATA,
	FONT,
	MESH,
	SHADER,
	TEXTURE,
	VIDEO,
	NARRAY,
	NSTRING
};

bool ParseBool(std::string str);
uint8_t ParseByte(std::string str);
int16_t ParseShort(std::string str);
uint16_t ParseUShort(std::string str);
float ParseFloat(std::string str);
int ParseInt(std::string str);
unsigned int ParseUInt(std::string str);
double ParseDouble(std::string str);
long long ParseLongLong(std::string str);
unsigned long long ParseULongLong(std::string str);

FVector2 ParseVector2(std::string str);
FVector3 ParseVector3(std::string str);
FVector4 ParseVector4(std::string str);
FColor ParseColor(std::string str);
FQuaternion ParseQuaternion(std::string str);
FCurve ParseCurve(std::string str);

AudioClip ParseAudio(std::string str);
Datatable ParseData(std::string str);
FontData* ParseFont(std::string str);
Material* ParseMaterial(std::string str);
MeshData* ParseMesh(std::string str);
Shader* ParseShader(std::string str);
Texture* ParseTexture(std::string str);

// ADD VIDEO HERE
// ADD ARRAY AND STRING HERE IF NECESSARY

/* BOOL, BYTE, SHORT, USHORT, FLOAT, INT, UINT, DOUBLE, LONG, ULONG,
	VECTOR2, VECTOR3, VECTOR4, COLOR, QUATERNION, CURVE, AUDIO,
	DATA, FONT, MESH, SHADER, TEXTURE, VIDEO, NARRAY, NSTRING*/