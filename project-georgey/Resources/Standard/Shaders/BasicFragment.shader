#version 330 core

out vec3 color;
in vec2 UV;

uniform sampler2D textureSampler;

void main()
{
	color = texture(textureSampler, UV).rgb;
}