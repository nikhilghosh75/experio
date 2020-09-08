#include "MeshMaterial.h"

MeshMaterial::MeshMaterial()
{
	this->shader = nullptr;
}

MeshMaterial::MeshMaterial(Shader * shader)
{
	this->shader = shader;
}

void MeshMaterial::SetMVP(const glm::mat4 M, const glm::mat4 V, const glm::mat4 P)
{
	glm::mat4 MVP = P * V * M;
	glm::mat3 MV3x3 = glm::mat3(V * M);

	shader->SetUniformMatrix4("MVP", MVP);

	PB_SET_MATERIAL_UNIFORM("M", M, SetUniformMatrix4);
	PB_SET_MATERIAL_UNIFORM("V", V, SetUniformMatrix4);
	PB_SET_MATERIAL_UNIFORM("P", P, SetUniformMatrix4);
	PB_SET_MATERIAL_UNIFORM("MV3x3", MV3x3, SetUniformMatrix3);
}

void MeshMaterial::SetLightingData(FLightData lightData)
{
	// EXPAND LATER
	shader->SetUniformVec3("LightWorldPosition",lightData.worldPosition);
	shader->SetUniformVec3("LightColor", (FVector3)lightData.color);
	shader->SetUniformFloat("LightPower", lightData.power);
}

void MeshMaterial::SetInternalUniforms()
{
	albedo->Bind(0);
	normal->Bind(1);
	specular->Bind(2);

	shader->SetUniformInt("albedoTexture", 0);
	shader->SetUniformInt("normalTexture", 1);
	shader->SetUniformInt("specularTexture", 2);
}