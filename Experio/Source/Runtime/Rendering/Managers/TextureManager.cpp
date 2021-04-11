#include "TextureManager.h"
#include "../../Files/Images/LImageOperations.h"
#include "../../Files/Images/ImageReader.h"

TextureSlot TextureManager::slots[MAX_TEXTURES];
std::string TextureManager::slotNames[MAX_TEXTURES];
uint16_t TextureManager::nextAvailibleSlot = 0;

static uint16_t texturesAllocated = 0;

TextureRef::TextureRef()
{
	this->texture = nullptr;
	this->textureID = 0;
}

TextureRef::TextureRef(uint16_t textureID)
{
	this->textureID = textureID;
	this->texture = TextureManager::slots[textureID].texture;

	TextureManager::slots[textureID].refCount++;
}

TextureRef::TextureRef(Texture * texture, uint16_t textureID)
{
	this->texture = texture;
	this->textureID = textureID;

	TextureManager::slots[textureID].refCount++;
}

TextureRef::TextureRef(const TextureRef & other)
{
	this->texture = other.texture;
	this->textureID = other.textureID;
	
	TextureManager::slots[textureID].refCount++;
}

TextureRef::~TextureRef()
{
	TextureManager::OnTextureDeleted(this->textureID);
}

TextureRef& TextureRef::operator=(const TextureRef& other)
{
	this->texture = other.texture;
	this->textureID = other.textureID;

	TextureManager::slots[textureID].refCount++;

	return *this;
}

bool TextureRef::IsNull()
{
	return this->texture == nullptr || this->textureID >= MAX_TEXTURES;
}

TextureSlot::TextureSlot()
{
	this->texture = nullptr;
	this->slotID = texturesAllocated;
	this->refCount = 0;

	texturesAllocated++;
}

void TextureSlot::DeleteTexture()
{
	if (this->texture != nullptr)
	{
		delete this->texture;
		this->texture = nullptr;
	}
}

void TextureManager::OnTextureDeleted(uint16_t slotID)
{
	if (slotID >= MAX_TEXTURES) return;
	TextureSlot& slot = slots[slotID];

	slot.refCount--;
	if (slot.refCount == 0)
	{
		slot.DeleteTexture();
		slotNames[slotID] = "";
		if (nextAvailibleSlot > slotID)
		{
			nextAvailibleSlot = slotID;
		}
	}
}

void TextureManager::FindNextAvailibleSlot()
{
	for (int i = 0; i < MAX_TEXTURES; i++)
	{
		if (slots[i].texture == nullptr && slots[i].refCount <= 0)
		{
			nextAvailibleSlot = i;
			return;
		}
	}
}

void TextureManager::Init()
{
	for (int i = 0; i < MAX_TEXTURES; i++)
	{
		slotNames[i] = "";
	}
}

TextureRef TextureManager::GetTexture(const std::string& str)
{
	for (uint16_t i = 0; i < MAX_TEXTURES; i++)
	{
		if (str == slotNames[i])
		{
			return TextureRef(i);
		}
	}
	return TextureRef(nullptr, MAX_TEXTURES);
}

TextureRef TextureManager::LoadTexture(const std::string& str)
{
	for (uint16_t i = 0; i < MAX_TEXTURES; i++)
	{
		if (str == slotNames[i])
		{
			return TextureRef(i);
		}
	}

	if (slots[nextAvailibleSlot].texture != nullptr)
	{
		FindNextAvailibleSlot();
	}
	
	slotNames[nextAvailibleSlot] = str;
	slots[nextAvailibleSlot].texture = new Texture(ImageReader::ReadFile(str.c_str()));
	slots[nextAvailibleSlot].refCount++;
	uint16_t lastAvailibleSlot = nextAvailibleSlot;
	FindNextAvailibleSlot();
	return TextureRef(lastAvailibleSlot);
}

bool TextureManager::IsTextureLoaded(const std::string& str)
{
	for (uint16_t i = 0; i < MAX_TEXTURES; i++)
	{
		if (str == slotNames[i])
		{
			return true;
		}
	}
	return false;
}

std::string TextureManager::GetNameOfTexture(const TextureRef & ref)
{
	return slotNames[ref.textureID];
}

size_t TextureManager::SizeOfLoadedTextures()
{
	size_t loadedSize = 0;

	for (size_t i = 0; i < MAX_TEXTURES; i++)
	{
		if (slots[i].texture != nullptr)
		{
			loadedSize += LImageOperations::SizeOfImage(slots[i].texture);
		}
	}

	return loadedSize;
}

TextureSlot& TextureManager::GetNextAvailibleSlot()
{
	return slots[nextAvailibleSlot];
}

void TextureManager::ReserveSlot(uint16_t slotId, const std::string& slotName)
{
	slotNames[slotId] = slotName;
}
