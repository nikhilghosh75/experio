#language GLSL
#version 330 core

#shader vertex

layout(location = 0) in vec4 position;

void main()
{
	gl_Position = position;
}

#shader fragment

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}