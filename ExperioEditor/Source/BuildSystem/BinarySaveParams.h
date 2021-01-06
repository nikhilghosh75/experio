#pragma once
#include "../Framework/SaveParams.h"

void BinarySaveBool(bool param, std::ostream& stream);
void BinarySaveByte(int8_t param, std::ostream& stream);
void BinarySaveUByte(uint8_t param, std::ostream& stream);
void BinarySaveShort(short param, std::ostream& stream);
void BinarySaveUShort(uint16_t param, std::ostream& stream);
void BinarySaveFloat(float param, std::ostream& stream);
void BinarySaveInt(int param, std::ostream& stream);
void BinarySaveUInt(unsigned int param, std::ostream& stream);
void BinarySaveDouble(double param, std::ostream& stream);
void BinarySaveLongLong(long long param, std::ostream& stream);
void BinarySaveULongLong(uint64_t param, std::ostream& stream);

void BinarySaveVector2(FVector2 param, std::ostream& stream);
void BinarySaveVector3(FVector3 param, std::ostream& stream);
void BinarySaveVector4(FVector4 param, std::ostream& stream);
void BinarySaveColor(FColor param, std::ostream& stream);
void BinarySaveQuaternion(FQuaternion param, std::ostream& stream);
void BinarySaveRect(FRect param, std::ostream& stream);
void BinarySaveBox(FBox param, std::ostream& stream);
void BinarySaveCurve(FCurve param, std::ostream& stream);
void BinarySaveSphericalPoint(FSphericalPoint param, std::ostream& stream);

void BinarySaveAudio(FAudioClip param, std::ostream& stream);
void BinarySaveData(DataRef param, std::ostream& stream);
void BinarySaveFont(FontRef param, std::ostream& stream);
void BinarySaveMaterial(Material* param, std::ostream& stream);
void BinarySaveMesh(MeshRef param, std::ostream& stream);
void BinarySaveTexture(TextureRef param, std::ostream& stream);