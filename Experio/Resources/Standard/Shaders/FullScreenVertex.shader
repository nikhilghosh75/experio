#version 330 core

layout(location = 0) in vec2 vertexPosition;

out vec2 UV;

void main()
{
	gl_Position = vec4(vertexPosition, 0, 1);

	UV = (vertexPosition) + vec2(1, 1) / 2.0;
}