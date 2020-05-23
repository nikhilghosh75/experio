#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 modelNormal;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 LightWorldPosition;

out vec2 UV;
out vec3 WorldPosition;
out vec3 NormalCameraSpace;
out vec3 EyeDirectionCameraSpace;
out vec3 LightDirectionCameraSpace;

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
}