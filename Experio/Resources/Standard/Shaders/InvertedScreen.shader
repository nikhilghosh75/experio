#language GLSL
#version 330 core

#shader vertex

layout(location = 0) in vec2 vertexPosition;

out vec2 UV;

void main()
{
	gl_Position = vec4(vertexPosition, 0, 1);

	UV = (vertexPosition)+vec2(1, 1) / 2.0;
}

#shader fragment

in vec2 UV;
out vec4 color;
uniform sampler2D textureSampler;

void main()
{
	color = 1 - texture(textureSampler, UV);
}