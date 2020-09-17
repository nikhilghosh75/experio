#version 330 core

in vec2 UV;
out vec4 color;
uniform sampler2D textureSampler;

void main()
{
	color = 1 - texture(textureSampler, UV);
}