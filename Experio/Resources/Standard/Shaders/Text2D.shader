#language GLSL
#version 330 core

#shader vertex

layout(location = 0) in vec2 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec2 vertexOffset;

out vec2 UV;

void main()
{
	gl_Position = vec4(vertexPosition + vertexOffset, 0, 1);

	UV = vertexUV;
}

#shader fragment

in vec2 UV;

out vec4 color;

uniform sampler2D textureSampler;
uniform vec4 textColor;

void main()
{
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(textureSampler, UV).r);
	color = textColor * sampled;
	// color = sampled;
}