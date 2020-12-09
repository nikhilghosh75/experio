#pragma once
#include <string>

enum class EAssetType : uint8_t
{
	Audio,
	Animation,
	CPP,
	Data,
	Font,
	Image,
	H,
	Markup,
	Material,
	Mesh,
	Meta,
	NonEngineCode,
	Particle,
	Prefab,
	Shader,
	Scene,
	Text,
	Video,
	Directory,
	Unknown
};

// Directory should always be second to last
// Unknown should always be last

struct Filemask;

struct FFileCategory
{
	EAssetType type;
	bool isMeta;

	FFileCategory();
	FFileCategory(EAssetType type);
	FFileCategory(EAssetType type, bool isMeta);
	FFileCategory(std::string s);

	bool IsCode() const;
	bool IsParseable() const; // Modify as more file types become parseable
	bool IsEngineOnly() const;
	bool IsPreviwable() const;
};