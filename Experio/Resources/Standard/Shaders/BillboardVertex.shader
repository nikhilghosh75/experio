#version 330 core

layout(location = 0) in vec3 position;

out vec2 UV;

uniform vec3 cameraUpWorldSpace;
uniform vec3 cameraRightWorldSpace;
uniform mat4 VP;
uniform vec3 billboardPosition;
uniform vec3 billboardRotation;
uniform vec2 billboardSize;
uniform int billboardSizeType;
uniform int billboardOrientation;

// From Rendering/Billboard.h
int WorldSize = 10;
int FixedSize = 11;

vec3 CalculateVertexPositionWorldSpace()
{
	if (billboardSizeType == WorldSize)
	{
		return billboardPosition + (cameraRightWorldSpace * position.x * billboardSize.x) + (cameraUpWorldSpace * position.y * billboardSize.y);
	}
	else if (billboardSizeType == FixedSize)
	{
		return billboardPosition;
	}
	return vec3(0, 0, 0);
}

void main()
{
	vec3 vertexPositionWorldSpace = CalculateVertexPositionWorldSpace();

	gl_Position = VP * vec4(vertexPositionWorldSpace, 1.0f);

	if (billboardSizeType == FixedSize)
	{
		gl_Position /= gl_Position.w;
		gl_Position.xy += position.xy * vec2(0.2, 0.05);
	}

	UV = position.xy + vec2(0.5, 0.5);
}