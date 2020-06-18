#version 330 core

in vec2 UV;
in vec3 WorldPosition;
in vec3 NormalCameraSpace;
in vec3 EyeDirectionCameraSpace;
in vec3 LightDirectionCameraSpace;
in vec3 EyeDirectionTangentSpace;
in vec3 LightDirectionTangentSpace;

layout(location = 0) out vec3 color;
//out vec3 color;

uniform sampler2D albedoTexture;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;
uniform vec3 LightWorldPosition;
uniform vec3 LightColor;
uniform float LightPower;

void main()
{
	vec3 MaterialDiffuseColor = texture(albedoTexture, UV).rgb;
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);
	//vec3 MaterialSpecularColor = texture(specularTexture, UV).rgb * 0.3;

	float distance = length(LightWorldPosition - WorldPosition);

	vec3 TextureNormalTangentSpace = normalize(texture(normalTexture, vec2(UV.x, UV.y)).rgb * 2.0 - 1.0);

	vec3 n = TextureNormalTangentSpace;
	vec3 l = normalize(LightDirectionTangentSpace);
	float cosTheta = clamp(dot(n, l), 0, 1);

	vec3 E = normalize(EyeDirectionTangentSpace);
	vec3 R = reflect(-l, n);
	float cosAlpha = clamp(dot(E, R), 0, 1);

	vec3 Ambient = MaterialAmbientColor;
	vec3 Diffuse = MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance * distance);
	vec3 Specular = MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 5) / (distance * distance);

	color = Ambient + Diffuse + Specular;
	//color = texture(albedoTexture, UV).rgb;
}

/*
	vec3 MaterialDiffuseColor = texture(albedoTexture, UV).rgb;
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
*/