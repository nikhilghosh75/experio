#include "FontManager.h"
#include "../../Files/Font/LFontOperations.h"

FontSlot FontManager::slots[MAX_FONTS];
std::string FontManager::slotNames[MAX_FONTS];
uint16_t FontManager::nextAvailibleSlot;

static uint16_t fontsAllocated;

FontRef::FontRef()
{
	this->fontData = nullptr;
	this->fontID = MAX_FONTS;
}

FontRef::FontRef(uint16_t fontID)
{
	this->fontID = fontID;
	this->fontData = FontManager::slots[fontID].data;
	
	FontManager::slots[fontID].refCount++;
}

FontRef::FontRef(FontData * fontData, uint16_t fontID)
{
	this->fontID = fontID;
	this->fontData = fontData;

	FontManager::slots[fontID].refCount++;
}

FontRef::FontRef(const FontRef & other)
{
	this->fontID = other.fontID;
	this->fontData = other.fontData;

	FontManager::slots[this->fontID].refCount++;
}

FontRef::~FontRef()
{
	FontManager::OnFontDeleted(this->fontID);
}

FontRef& FontRef::operator=(const FontRef& other)
{
	this->fontData = other.fontData;
	this->fontID = other.fontID;

	FontManager::slots[fontID].refCount++;

	return *this;
}

bool FontRef::IsNull()
{
	return this->fontData == nullptr || this->fontID >= MAX_FONTS;
}

FontSlot::FontSlot()
{
	this->data = nullptr;
	this->slotID = fontsAllocated;
	this->refCount = 0;

	fontsAllocated++;
}

void FontSlot::DeleteFont()
{
	if (this->data != nullptr)
	{
		delete this->data;
		this->data = nullptr;
	}
}

void FontManager::OnFontDeleted(uint16_t slotIndex)
{
	if (slotIndex >= MAX_FONTS) return;
	FontSlot& slot = slots[slotIndex];

	slot.refCount--;
	if (slot.refCount == 0)
	{
		slot.DeleteFont();
		slotNames[slotIndex] = "";
		if (nextAvailibleSlot > slotIndex)
		{
			nextAvailibleSlot = slotIndex;
		}
	}
}

void FontManager::FindNextAvailibleSlot()
{
	for (int i = 0; i < MAX_FONTS; i++)
	{
		if (slots[i].data == nullptr && slots[i].refCount <= 0)
		{
			nextAvailibleSlot = i;
			return;
		}
	}
}

void FontManager::Init()
{
	for (int i = 0; i < MAX_FONTS; i++)
	{
		slotNames[i] = "";
	}
}

FontRef FontManager::GetFont(const std::string & str)
{
	for (uint16_t i = 0; i < MAX_FONTS; i++)
	{
		if (str == slotNames[i])
		{
			return FontRef(i);
		}
	}
	return FontRef(nullptr, MAX_FONTS);
}

FontRef FontManager::LoadFont(const std::string & str)
{
	for (uint16_t i = 0; i < MAX_FONTS; i++)
	{
		if (str == slotNames[i])
		{
			return FontRef(i);
		}
	}

	if (slots[nextAvailibleSlot].data != nullptr)
	{
		FindNextAvailibleSlot();
	}

	slotNames[nextAvailibleSlot] = str;
	slots[nextAvailibleSlot].data = FontReader::ReadFile(str.c_str());
	slots[nextAvailibleSlot].refCount++;
	uint16_t lastAvailibleSlot = nextAvailibleSlot;
	FindNextAvailibleSlot();
	return FontRef(lastAvailibleSlot);
}

bool FontManager::IsFontLoaded(const std::string & str)
{
	for (uint16_t i = 0; i < MAX_FONTS; i++)
	{
		if (str == slotNames[i])
		{
			return true;
		}
	}
	return false;
}

std::string FontManager::GetNameOfFont(const FontRef & ref)
{
	return slotNames[ref.fontID];
}

size_t FontManager::SizeOfLoadedFonts()
{
	size_t loadedSize = 0;

	for (size_t i = 0; i < MAX_FONTS; i++)
	{
		if (slots[i].data != nullptr)
		{
			loadedSize += LFontOperations::SizeOf(*slots[i].data);
		}
	}

	return loadedSize;
}
