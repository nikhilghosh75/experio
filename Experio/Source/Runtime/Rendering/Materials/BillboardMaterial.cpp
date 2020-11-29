#include "BillboardMaterial.h"

BillboardMaterial::BillboardMaterial(Shader * shader)
{
	this->shader = shader;
}

BillboardMaterial::BillboardMaterial(Shader * shader, uint32_t id)
{
	this->shader = shader;
	this->id = id;
}

void BillboardMaterial::SetCameraVP(glm::mat4 V, glm::mat4 P, FVector3 cameraUp, FVector3 cameraRight)
{
	glm::mat4 VP = P * V;

	shader->SetUniformMatrix4("VP", VP);
	shader->SetUniformVec3("cameraUpWorldSpace", cameraUp);
	shader->SetUniformVec3("cameraRightWorldSpace", cameraRight);
}

void BillboardMaterial::SetBillboardData(FVector3 position, FVector3 rotation, FVector2 size)
{
	shader->SetUniformVec3("billboardPosition", position);
	shader->SetUniformVec3("billboardRotation", rotation);
	shader->SetUniformVec2("billboardSize", size);
}

void BillboardMaterial::SetInternalUniforms()
{
	shader->SetUniformInt("albedoTexture", 0);
}
