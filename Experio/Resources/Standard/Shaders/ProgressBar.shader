#language GLSL
#version 330 core

#shader vertex

layout(location = 0) in vec2 position;
layout(location = 1) in vec4 color;

out vec4 outColor;

void main()
{
	gl_Position = vec4(position, 0, 1);

	outColor = color;
}

#shader fragment

in vec4 outColor;

out vec4 color;

void main()
{
	color = outColor;
}