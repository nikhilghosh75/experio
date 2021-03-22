#pragma once

#include "../Texture.h"
#include <string>

// This defines the maximum amount of textures that can be loaded at one time
#define MAX_TEXTURES 128

class TextureManager;

class TextureRef
{
	friend class TextureManager;

	uint16_t textureID;
public:
	TextureRef();
	TextureRef(uint16_t textureID);
	TextureRef(Texture* texture, uint16_t textureID);
	TextureRef(const TextureRef& other);

	~TextureRef();

	Texture* texture;

	Texture* operator->() { return texture; }
	const Texture* operator->() const { return texture; }

	Texture& operator*() { return *texture; }
	const Texture& operator*() const { return *texture; }

	bool IsNull();
};

struct TextureSlot
{
	Texture* texture;
	uint16_t slotID;
	uint16_t refCount;

	TextureSlot();

	void DeleteTexture();
};

class TextureManager
{
	friend class TextureRef;

	static TextureSlot slots[MAX_TEXTURES];
	static std::string slotNames[MAX_TEXTURES];

	static uint16_t nextAvailibleSlot;

	static void OnTextureDeleted(uint16_t slotID);

	static void FindNextAvailibleSlot();
public:
	static void Init();

	static TextureRef GetTexture(const std::string& str);

	static TextureRef LoadTexture(const std::string& str);

	static bool IsTextureLoaded(const std::string& str);

	static std::string GetNameOfTexture(const TextureRef& ref);

	static size_t SizeOfLoadedTextures();
};