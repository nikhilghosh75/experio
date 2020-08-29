#version 330 core

in vec4 particleColor;

layout(location = 0) out vec4 color;

void main()
{
	color = particleColor;
}