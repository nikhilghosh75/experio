#pragma once
#include <string>
#include "../Debug/Debug.h"
#include "../Containers/LString.h"
#include "../Files/LFileOperations.h"

#include "../Audio/FAudioClip.h"
#include "../Data/DataManager.h"
#include "../Files/FileRef.h"
#include "../Files/TextRef.h"
#include "../Files/Font/FontReader.h"
#include "../Files/Images/ImageReader.h"
#include "../Files/Mesh/MeshReader.h"
#include "../Math/FVector2.h"
#include "../Math/FVector3.h"
#include "../Math/FVector4.h"
#include "../Math/FQuaternion.h"
#include "../Math/FBox.h"
#include "../Math/FColor.h"
#include "../Math/FCurve.h"
#include "../Math/FRect.h"
#include "../Math/FSphericalPoint.h"
#include "../Rendering/Materials/Material.h"
#include "../Rendering/Shaders/Shader.h"
#include "../Rendering/Shaders/ShaderReader.h"
#include "../Rendering/Managers/TextureManager.h"
#include "../Rendering/Managers/MeshManager.h"
#include "../Rendering/Managers/FontManager.h"

class TextureRef;
class MeshRef;

/// <summary>
/// A set of function for parsing text data into Experio types
/// </summary>

enum class EParamType
{
	BOOL,
	BYTE,
	UBYTE,
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
	RECT,
	BOX,
	SPHERICALPOINT,
	CURVE,
	MATERIAL,
	AUDIO,
	DATA,
	FILE,
	TEXT,
	FONT,
	MESH,
	SHADER,
	TEXTURE,
	VIDEO,
	STRING,
	NARRAY,
};

bool ParseBool(std::string str);
int8_t ParseByte(std::string str);
uint8_t ParseUByte(std::string str);
int16_t ParseShort(std::string str);
uint16_t ParseUShort(std::string str);
float ParseFloat(std::string str);
int ParseInt(std::string str);
unsigned int ParseUInt(std::string str);
double ParseDouble(std::string str);
long long ParseLongLong(std::string str);
unsigned long long ParseULongLong(std::string str);

std::string ParseString(std::string str);

FVector2 ParseVector2(std::string str);
FVector3 ParseVector3(std::string str);
FVector4 ParseVector4(std::string str);
FColor ParseColor(std::string str);
FQuaternion ParseQuaternion(std::string str);
FRect ParseRect(std::string str);
FBox ParseBox(std::string str);
FCurve ParseCurve(std::string str);
FSphericalPoint ParseSphericalPoint(std::string str);

FAudioClip ParseAudio(std::string str);
DataRef ParseData(std::string str);
FileRef ParseFile(std::string str);
FontRef ParseFont(std::string str);
Material* ParseMaterial(std::string str);
MeshRef ParseMesh(std::string str);
Shader* ParseShader(std::string str);
TextRef ParseTextRef(std::string str);
TextureRef ParseTexture(std::string str);

// ADD VIDEO HERE
// ADD ARRAY AND STRING HERE IF NECESSARY
