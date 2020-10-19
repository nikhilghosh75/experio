#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 modelNormal;
layout(location = 3) in vec3 modelTangent;
layout(location = 4) in vec3 modelBitangent;
layout(location = 5) in vec4 color;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;

out vec3 WorldPosition;
out vec4 WorldColor;

void main()
{
	gl_Position = MVP * position;

	WorldPosition = (M * position).xyz;
	WorldColor = color;
}