#pragma once

#include "../../Files/Font/FontReader.h"
#include <string>

// This defines the maximum amount of fonts that can be loaded at one time
#define MAX_FONTS 64

class FontManager;

class FontRef
{
	friend class FontManager;

public:
	FontRef();
	FontRef(uint16_t fontID);
	FontRef(FontData* fontData, uint16_t fontID);
	FontRef(const FontRef& other);

	~FontRef();

	FontRef& operator=(const FontRef& other);

	uint16_t fontID;

	FontData* fontData;

	FontData* operator->() { return this->fontData; };
	const FontData* operator->() const { return this->fontData; };

	bool IsNull();
};

struct FontSlot
{
	FontData* data;
	uint16_t slotID;
	uint16_t refCount;
	bool persistInMemory;

	FontSlot();

	void DeleteFont();
};

class FontManager
{
	friend class FontRef;

	static FontSlot slots[MAX_FONTS];
	static std::string slotNames[MAX_FONTS];

	static uint16_t nextAvailibleSlot;

	static void OnFontDeleted(uint16_t slotIndex);

	static void FindNextAvailibleSlot();
public:
	static bool CanStoreFont();

	static void Init();

	static FontRef GetFont(const std::string& str);
	static FontRef GetFont(uint16_t slotIndex);

	static FontRef LoadFont(const std::string& str, bool persistInMemory = false);

	static bool IsFontLoaded(const std::string& str);

	static std::string GetNameOfFont(const FontRef& ref);

	static size_t NumLoadedFonts();

	static size_t SizeOfLoadedFonts();
};