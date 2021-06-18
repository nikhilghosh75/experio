#include "MeshManager.h"
#include "../../Files/Mesh/LMeshOperations.h"

MeshSlot MeshManager::slots[MAX_MESHES];
std::string MeshManager::slotNames[MAX_MESHES];
uint16_t MeshManager::nextAvailibleSlot = 0;

static uint16_t meshesAllocated;

MeshRef::MeshRef()
{
	this->meshData = nullptr;
	this->meshID = 0;
}

MeshRef::MeshRef(uint16_t meshID)
{
	this->meshID = meshID;
	this->meshData = MeshManager::slots[meshID].data;
	
	MeshManager::slots[meshID].refCount++;
}

MeshRef::MeshRef(MeshData * meshData, uint16_t meshID)
{
	this->meshID = meshID;
	this->meshData = meshData;

	MeshManager::slots[meshID].refCount++;
}

MeshRef::MeshRef(const MeshRef & other)
{
	this->meshID = other.meshID;
	this->meshData = other.meshData;

	MeshManager::slots[meshID].refCount++;
}

MeshRef& MeshRef::operator=(const MeshRef& other)
{
	this->meshData = other.meshData;
	this->meshID = other.meshID;

	MeshManager::slots[meshID].refCount++;

	return *this;
}

MeshRef::~MeshRef()
{
	MeshManager::OnMeshDeleted(this->meshID);
}

bool MeshRef::IsNull()
{
	return this->meshData == nullptr || this->meshID >= MAX_MESHES;
}

MeshSlot::MeshSlot()
{
	this->data = nullptr;
	this->slotID = meshesAllocated;
	this->refCount = 0;
	
	meshesAllocated++;
}

void MeshSlot::DeleteMesh()
{
	if (this->data != nullptr)
	{
		delete this->data;
		this->data = nullptr;
	}
}

void MeshManager::OnMeshDeleted(uint16_t slotIndex)
{
	if (slotIndex >= MAX_MESHES) return;
	MeshSlot& slot = slots[slotIndex];

	slot.refCount--;
	if (slot.refCount == 0)
	{
		slot.DeleteMesh();
		slotNames[slotIndex] = "";
		if (nextAvailibleSlot > slotIndex)
		{
			nextAvailibleSlot = slotIndex;
		}
	}
}

void MeshManager::FindNextAvailibleSlot()
{
	for (int i = 0; i < MAX_MESHES; i++)
	{
		if (slots[i].data == nullptr && slots[i].refCount <= 0)
		{
			nextAvailibleSlot = i;
			return;
		}
	}
}

bool MeshManager::CanStoreMesh()
{
	return NumLoadedMeshes() < MAX_MESHES - 1;
}

void MeshManager::Init()
{
	for (int i = 0; i < MAX_MESHES; i++)
	{
		slotNames[i] = "";
	}
}

MeshRef MeshManager::GetMesh(const std::string& str)
{
	for (uint16_t i = 0; i < MAX_MESHES; i++)
	{
		if (str == slotNames[i])
		{
			return MeshRef(i);
		}
	}
	return MeshRef(nullptr, MAX_MESHES);
}

MeshRef MeshManager::LoadMesh(const std::string& str)
{
	for (uint16_t i = 0; i < MAX_MESHES; i++)
	{
		if (str == slotNames[i])
		{
			return MeshRef(i);
		}
	}

	if (slots[nextAvailibleSlot].data != nullptr)
	{
		FindNextAvailibleSlot();
	}

	slotNames[nextAvailibleSlot] = str;
	slots[nextAvailibleSlot].data = MeshReader::ReadFile(str.c_str());
	slots[nextAvailibleSlot].refCount++;
	uint16_t lastAvailibleSlot = nextAvailibleSlot;
	FindNextAvailibleSlot();
	return MeshRef(lastAvailibleSlot);
}

bool MeshManager::IsMeshLoaded(const std::string& str)
{
	for (uint16_t i = 0; i < MAX_MESHES; i++)
	{
		if (str == slotNames[i])
		{
			return true;
		}
	}
	return false;
}

std::string MeshManager::GetNameOfMesh(const MeshRef& ref)
{
	return slotNames[ref.meshID];
}

size_t MeshManager::NumLoadedMeshes()
{
	size_t numLoadedMeshes = 0;
	for (uint16_t i = 0; i < MAX_MESHES; i++)
	{
		if (slots[i].data != nullptr)
			numLoadedMeshes++;
	}
	return numLoadedMeshes;
}

size_t MeshManager::SizeOfLoadedMeshes()
{
	size_t loadedSize = 0;

	for (size_t i = 0; i < MAX_MESHES; i++)
	{
		if (slots[i].data != nullptr)
		{
			loadedSize += LMeshOperations::SizeOfMesh(*slots[i].data);
		}
	}

	return loadedSize;
}
