#pragma once
#include "Material.h"
#include "../../../Dependencies/glm/glm/glm.hpp"
#include "../Managers/TextureManager.h"
#include "../LightData.h"

class MeshMaterial : public Material
{
public:
	MeshMaterial();
	MeshMaterial(Shader* shader);
	MeshMaterial(Shader* shader, uint32_t id);

	TextureRef albedo;
	TextureRef normal;
	TextureRef specular;

	bool useLightingData = true;

	void SetMVP(const glm::mat4 M, const glm::mat4 V, const glm::mat4 P);
	void SetLightingData(const FLightData lightData);

	virtual void SetInternalUniforms() override;
};