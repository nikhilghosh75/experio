#language GLSL
#version 330 core

#shader vertex

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 modelNormal;
layout(location = 3) in vec3 modelTangent;
layout(location = 4) in vec3 modelBitangent;

uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform mat3 MV3x3;
uniform vec3 LightWorldPosition;

out vec2 UV;
out vec3 WorldPosition;
out vec3 NormalCameraSpace;
out vec3 EyeDirectionCameraSpace;
out vec3 LightDirectionCameraSpace;
out vec3 EyeDirectionTangentSpace;
out vec3 LightDirectionTangentSpace;

void main()
{
	gl_Position = MVP * position;

	WorldPosition = (M * position).xyz;

	vec3 positionCameraSpace = (V * M * position).xyz;
	EyeDirectionCameraSpace = vec3(0, 0, 0) - positionCameraSpace;

	vec3 LightPositionCameraSpace = (V * vec4(LightWorldPosition, 1)).xyz;
	LightDirectionCameraSpace = LightPositionCameraSpace + EyeDirectionCameraSpace;

	NormalCameraSpace = (V * M * vec4(modelNormal, 0)).xyz;

	UV = vertexUV;

	vec3 cameraTangent = MV3x3 * modelTangent;
	vec3 cameraBitangent = MV3x3 * modelBitangent;
	vec3 cameraNormal = MV3x3 * modelNormal;

	mat3 TBN = transpose(mat3(
		cameraTangent, cameraBitangent, cameraNormal
	));

	EyeDirectionTangentSpace = TBN * EyeDirectionCameraSpace;
	LightDirectionTangentSpace = TBN * LightDirectionCameraSpace;
}

#shader fragment

in vec2 UV;
in vec3 WorldPosition;
in vec3 NormalCameraSpace;
in vec3 EyeDirectionCameraSpace;
in vec3 LightDirectionCameraSpace;
in vec3 EyeDirectionTangentSpace;
in vec3 LightDirectionTangentSpace;

layout(location = 0) out vec3 color;

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