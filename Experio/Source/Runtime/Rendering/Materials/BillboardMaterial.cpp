#include "BillboardMaterial.h"

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
	billboardTexture->Bind(0);
	shader->SetUniformInt("albedoTexture", 0);
}
