#include "SaveParams.h"

#include "../Core/EditorApplication.h"

void SaveBool(bool param, std::ostream & stream)
{
	if (param)
	{
		stream << "true";
	}
	else
	{
		stream << "false";
	}
}

void SaveByte(int8_t param, std::ostream & stream)
{
	stream << (unsigned short)param;
}

void SaveUByte(uint8_t param, std::ostream & stream)
{
	stream << (unsigned short)param;
}

void SaveShort(short param, std::ostream & stream)
{
	stream << param;
}

void SaveUShort(uint16_t param, std::ostream & stream)
{
	stream << param;
}

void SaveFloat(float param, std::ostream & stream)
{
	stream << param;
}

void SaveInt(int param, std::ostream & stream)
{
	stream << param;
}

void SaveUInt(unsigned int param, std::ostream & stream)
{
	stream << param;
}

void SaveDouble(double param, std::ostream & stream)
{
	stream << param;
}

void SaveLongLong(long long param, std::ostream & stream)
{
	stream << param;
}

void SaveULongLong(uint64_t param, std::ostream & stream)
{
	stream << param;
}

void SaveString(std::string str, std::ostream& stream)
{
	stream << str;
}

void SaveVector2(FVector2 param, std::ostream & stream)
{
	stream << param.x << " " << param.y;
}

void SaveVector3(FVector3 param, std::ostream & stream)
{
	stream << param.x << " " << param.y << " " << param.z;
}

void SaveVector4(FVector4 param, std::ostream & stream)
{
	stream << param.w << " " << param.x << " " << param.y << " " << param.z;
}

void SaveColor(FColor param, std::ostream & stream)
{
	stream << param.r << " " << param.g << " " << param.b << " " << param.a;
}

void SaveQuaternion(FQuaternion param, std::ostream & stream)
{
	stream << param.x << " " << param.y << " " << param.z << " " << param.w;
}

void SaveRect(FRect param, std::ostream & stream)
{
	stream << param.min.x << " " << param.min.y << " " << param.max.x << " " << param.max.y;
}

void SaveBox(FBox param, std::ostream & stream)
{
	stream << param.min.x << " " << param.min.y << " " << param.min.z 
		<< " " << param.max.x << " " << param.max.y << " " << param.max.z;
}

void SaveCurve(FCurve param, std::ostream & stream)
{
	Debug::LogError("THIS FUNCTION IS NOT COMPLETE YET");
}

void SaveSphericalPoint(FSphericalPoint param, std::ostream & stream)
{
	stream << param.radius << " " << param.polar << " " << param.azimuth;
}

void SaveAudio(FAudioClip param, std::ostream & stream)
{
	Debug::LogError("THIS FUNCTION IS NOT COMPLETE YET");
}

void SaveData(DataRef& param, std::ostream & stream)
{
	std::string fullFilePath = DataManager::GetNameOfFont(param);
	std::string shortenedFilePath = EditorApplication::GetShortenedFilePath(fullFilePath);
	stream << shortenedFilePath;
}

void SaveFile(FileRef& param, std::ostream & stream)
{
	std::string shortenedFilePath = EditorApplication::GetShortenedFilePath(param.filepath);
	stream << shortenedFilePath;
}

void SaveFont(FontRef& param, std::ostream & stream)
{
	std::string fullFilePath = FontManager::GetNameOfFont(param);
	std::string shortenedFilePath = EditorApplication::GetShortenedFilePath(fullFilePath);
	stream << shortenedFilePath;
}

void SaveMaterial(Material * param, std::ostream & stream)
{
	stream << "?Standard?/Materials/Test.material";
	Debug::LogError("THIS FUNCTION IS NOT COMPLETE YET");
}

void SaveMesh(MeshRef& param, std::ostream & stream)
{
	std::string fullFilePath = MeshManager::GetNameOfMesh(param);
	std::string shortenedFilePath = EditorApplication::GetShortenedFilePath(fullFilePath);
	stream << shortenedFilePath;
}

void SaveTextRef(TextRef& param, std::ostream& stream)
{
	std::string shortenedFilePath = EditorApplication::GetShortenedFilePath(param.filepath);
	stream << shortenedFilePath;
}

void SaveTexture(TextureRef& param, std::ostream & stream)
{
	std::string fullFilePath = TextureManager::GetNameOfTexture(param);
	std::string shortenedFilePath = EditorApplication::GetShortenedFilePath(fullFilePath);
	stream << shortenedFilePath;
}
