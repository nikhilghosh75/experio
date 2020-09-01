#pragma once

#include "Material.h"
#include "../Texture.h"
#include "../../Math/FVector3.h"
#include "../../Math/FVector2.h"

class BillboardMaterial : Material
{
public:
	Texture* billboardTexture;

	void SetCameraVP(glm::mat4 V, glm::mat4 P, FVector3 cameraUp, FVector3 cameraRight);
	void SetBillboardData(FVector3 position, FVector3 rotation, FVector2 size);

	virtual void SetInternalUniforms() override;
};