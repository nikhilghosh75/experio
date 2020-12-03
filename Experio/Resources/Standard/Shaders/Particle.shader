#language GLSL
#version 330 core

#shader vertex

layout(location = 0) in vec3 vertex; // Modelspace
layout(location = 1) in vec3 position; // Worldspace
layout(location = 2) in vec4 color;

uniform mat4 VP;

out vec4 particleColor;

mat4 TRS(vec3 position, vec3 rotation, vec3 scale)
{
	mat4 translation = mat4(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		position.x, position.y, position.z, 1.0
	);

	mat4 rotating = mat4(1.0);
	mat4 scaling = mat4(
		scale.x, 0.0, 0.0, 0.0,
		0.0, scale.y, 0.0, 0.0,
		0.0, 0.0, scale.z, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	return translation * rotating * scaling;
}

void main()
{
	mat4 M = TRS(position, vec3(0.0, 0.0, 0.0), vec3(0.1, 0.1, 0.1));
	gl_Position = VP * M * vec4(vertex, 1.0);

	particleColor = color;
}

#shader fragment

in vec4 particleColor;

layout(location = 0) out vec4 color;

void main()
{
	color = particleColor;
}