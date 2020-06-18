#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 modelNormal;
layout(location = 3) in vec3 modelTangent;
layout(location = 4) in vec3 modelBitangent;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;
uniform vec3 LightWorldPosition;

out vec2 UV;
out vec3 WorldPosition;
out vec3 NormalCameraSpace;
out vec3 EyeDirectionCameraSpace;
out vec3 LightDirectionCameraSpace;
out vec3 EyeDirectionTangentSpace;
out vec3 LightDirectionTangentSpace;

void main()
{
	gl_Position = MVP * position;

	WorldPosition = (M * position).xyz;

	vec3 positionCameraSpace = (V * M * position).xyz;
	EyeDirectionCameraSpace = vec3(0, 0, 0) - positionCameraSpace;

	vec3 LightPositionCameraSpace = (V * vec4(LightWorldPosition, 1)).xyz;
	LightDirectionCameraSpace = LightPositionCameraSpace + EyeDirectionCameraSpace;

	NormalCameraSpace = (V * M * vec4(modelNormal, 0)).xyz;

	UV = vertexUV;

	vec3 cameraTangent = MV3x3 * modelTangent;
	vec3 cameraBitangent = MV3x3 * modelBitangent;
	vec3 cameraNormal = MV3x3 * modelNormal;

	mat3 TBN = transpose(mat3(
		cameraTangent, cameraBitangent, cameraNormal
	));

	EyeDirectionTangentSpace = TBN * EyeDirectionCameraSpace;
	LightDirectionTangentSpace = TBN * LightDirectionCameraSpace;
}