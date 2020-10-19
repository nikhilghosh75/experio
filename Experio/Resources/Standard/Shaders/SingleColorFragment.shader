#version 330 core

in vec3 WorldPosition;
in vec4 WorldColor;

layout(location = 0) out vec3 color;

void main()
{
	color = vec3(WorldColor);
	// color = vec3(1, 0, 0);
}