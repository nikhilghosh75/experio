#pragma once
#include "../../Files/Mesh/MeshReader.h"
#include <string>

// This defines the maximum amount of meshes that can be loaded at one time
#define MAX_MESHES 96

class MeshManager;

class MeshRef
{
	friend class MeshManager;

	uint16_t meshID;
public:
	MeshRef();
	MeshRef(uint16_t meshID);
	MeshRef(MeshData* meshData, uint16_t meshID);
	MeshRef(const MeshRef& other);

	MeshRef& operator=(const MeshRef& other);

	~MeshRef();

	MeshData* meshData;

	MeshData* operator->() { return this->meshData; };
	const MeshData* operator->() const { return this->meshData; };

	bool IsNull();
};

struct MeshSlot
{
	MeshData* data;
	uint16_t slotID;
	uint16_t refCount;

	MeshSlot();

	void DeleteMesh();
};

class MeshManager
{
	friend class MeshRef;

	static MeshSlot slots[MAX_MESHES];
	static std::string slotNames[MAX_MESHES];

	static uint16_t nextAvailibleSlot;

	static void OnMeshDeleted(uint16_t slotIndex);

	static void FindNextAvailibleSlot();
public:
	static void Init();

	static MeshRef GetMesh(const std::string& str);

	static MeshRef LoadMesh(const std::string& str);

	static bool IsMeshLoaded(const std::string& str);

	static std::string GetNameOfMesh(const MeshRef& ref);

	static size_t SizeOfLoadedMeshes();
};