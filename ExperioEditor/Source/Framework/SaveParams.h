#pragma once
#include "Runtime/Framework/Params.h"
#include <fstream>

void SaveBool(bool param, std::ostream& stream);
void SaveByte(uint8_t param, std::ostream& stream);
void SaveShort(short param, std::ostream& stream);
void SaveUShort(uint16_t param, std::ostream& stream);
void SaveFloat(float param, std::ostream& stream);
void SaveInt(int param, std::ostream& stream);
void SaveUInt(unsigned int param, std::ostream& stream);
void SaveDouble(double param, std::ostream& stream);
void SaveLongLong(long long param, std::ostream& stream);
void SaveULongLong(uint64_t param, std::ostream& stream);

void SaveVector2(FVector2 param, std::ostream& stream);
void SaveVector3(FVector3 param, std::ostream& stream);
void SaveVector4(FVector4 param, std::ostream& stream);
void SaveColor(FColor param, std::ostream& stream);
void SaveQuaternion(FQuaternion param, std::ostream& stream);
void SaveRect(FRect param, std::ostream& stream);
void SaveCurve(FCurve param, std::ostream& stream);
void SaveSphericalPoint(FSphericalPoint param, std::ostream& stream);

void SaveAudio(FAudioClip param, std::ostream& stream);
void SaveData(Datatable param, std::ostream& stream);
void SaveFont(FontData* param, std::ostream& stream);
void SaveMaterial(Material* param, std::ostream& stream);
void SaveMesh(MeshRef param, std::ostream& stream);
void SaveTexture(TextureRef param, std::ostream& stream);