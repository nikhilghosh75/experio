#include "BinarySaveParams.h"
#include "AssetMapSaver.h"

void BinarySaveBool(bool param, std::ostream & stream)
{
	stream.write((char*)&param, 1);
}

void BinarySaveByte(int8_t param, std::ostream & stream)
{
	stream.write((char*)&param, 1);
}

void BinarySaveUByte(uint8_t param, std::ostream & stream)
{
	stream.write((char*)&param, 1);
}

void BinarySaveShort(short param, std::ostream & stream)
{
	stream.write((char*)&param, 2);
}

void BinarySaveUShort(uint16_t param, std::ostream & stream)
{
	stream.write((char*)&param, 2);
}

void BinarySaveFloat(float param, std::ostream & stream)
{
	stream.write((char*)&param, 4);
}

void BinarySaveInt(int param, std::ostream & stream)
{
	stream.write((char*)&param, 4);
}

void BinarySaveUInt(unsigned int param, std::ostream & stream)
{
	stream.write((char*)&param, 4);
}

void BinarySaveDouble(double param, std::ostream & stream)
{
	stream.write((char*)&param, 8);
}

void BinarySaveLongLong(long long param, std::ostream & stream)
{
	stream.write((char*)&param, 8);
}

void BinarySaveULongLong(uint64_t param, std::ostream & stream)
{
	stream.write((char*)&param, 8);
}

void BinarySaveVector2(FVector2 param, std::ostream & stream)
{
	stream.write((char*)&param, 8);
}

void BinarySaveVector3(FVector3 param, std::ostream & stream)
{
	stream.write((char*)&param, 12);
}

void BinarySaveVector4(FVector4 param, std::ostream & stream)
{
	stream.write((char*)&param, 12);
}

void BinarySaveColor(FColor param, std::ostream & stream)
{
	stream.write((char*)&param, 16);
}

void BinarySaveQuaternion(FQuaternion param, std::ostream & stream)
{
	stream.write((char*)&param, 16);
}

void BinarySaveRect(FRect param, std::ostream & stream)
{
	stream.write((char*)&param, 16);
}

void BinarySaveBox(FBox param, std::ostream & stream)
{
	stream.write((char*)&param, 24);
}

void BinarySaveCurve(FCurve param, std::ostream & stream)
{
	Debug::LogError("Save Function has not been implemented");
}

void BinarySaveSphericalPoint(FSphericalPoint param, std::ostream & stream)
{
	stream.write((char*)&param, 12);
}

void BinarySaveAudio(FAudioClip param, std::ostream & stream)
{
	Debug::LogError("Save Function has not been implemented");
}

void BinarySaveData(Datatable param, std::ostream & stream)
{
	Debug::LogError("Save Function has not been implemented");
}

void BinarySaveFont(FontRef param, std::ostream & stream)
{
	uint32_t assetId = AssetMapSaver::GetIndexOfAsset(FontManager::GetNameOfFont(param));
	stream.write((char*)&assetId, 4);
}

void BinarySaveMaterial(Material * param, std::ostream & stream)
{
	Debug::LogError("Save Function has not been implemented");
}

void BinarySaveMesh(MeshRef param, std::ostream & stream)
{
	uint32_t assetId = AssetMapSaver::GetIndexOfAsset(MeshManager::GetNameOfMesh(param));
	stream.write((char*)&assetId, 4);
}

void BinarySaveTexture(TextureRef param, std::ostream & stream)
{
	uint32_t assetId = AssetMapSaver::GetIndexOfAsset(TextureManager::GetNameOfTexture(param));
	stream.write((char*)&assetId, 4);
}
