#version 330 core

in vec2 UV;
in vec3 WorldPosition;
in vec3 NormalCameraSpace;
in vec3 EyeDirectionCameraSpace;
in vec3 LightDirectionCameraSpace;

out vec3 color;

uniform sampler2D textureSampler;
uniform vec3 LightWorldPosition;
uniform vec3 LightColor;
uniform float LightPower;

void main()
{
	vec3 MaterialDiffuseColor = texture(textureSampler, UV).rgb;
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

	float distance = length(LightWorldPosition - WorldPosition);

	vec3 n = normalize(NormalCameraSpace);
	vec3 l = normalize(LightDirectionCameraSpace);
	float cosTheta = clamp(dot(n, l), 0, 1);

	vec3 E = normalize(EyeDirectionCameraSpace);
	vec3 R = reflect(-l, n);
	float cosAlpha = clamp(dot(E, R), 0, 1);

	vec3 Ambient = MaterialAmbientColor;
	vec3 Diffuse = MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance * distance);
	vec3 Specular = MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 5) / (distance * distance);

	color = Ambient + Diffuse + Specular;
	//color = vec3(1.0, 1.0, 1.0);
}