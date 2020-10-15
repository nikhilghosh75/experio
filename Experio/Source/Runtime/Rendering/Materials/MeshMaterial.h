#pragma once
#include "Material.h"
#include "../../../Dependencies/glm/glm/glm.hpp"
#include "../Texture.h"
#include "../LightData.h"

class MeshMaterial : public Material
{
public:
	MeshMaterial();
	MeshMaterial(Shader* shader);

	Texture* albedo;
	Texture* normal;
	Texture* specular;

	bool useLightingData = true;

	void SetMVP(const glm::mat4 M, const glm::mat4 V, const glm::mat4 P);
	void SetLightingData(const FLightData lightData);

	virtual void SetInternalUniforms() override;
};