#pragma once
#include <string>

enum class EAssetType : uint8_t
{
	Audio,
	Animation,
	CPP,
	Data,
	Directory,
	Font,
	Image,
	H,
	Material,
	Mesh,
	Meta,
	NonEngineCode,
	Particle,
	Prefab,
	Shader,
	Scene,
	Text,
	Unknown,
	Video
};

struct FFileCategory
{
	EAssetType type;
	bool isMeta;

	FFileCategory();
	FFileCategory(std::string s);

	bool IsCode() const;
};