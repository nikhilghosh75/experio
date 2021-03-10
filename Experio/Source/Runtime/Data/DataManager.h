#pragma once

#include "Datatable.h"
#include <string>

/// <summary>
/// A set of classes designed to manage the datatables in the game
/// </summary>

// This defines the maximum amount of datatables that can be loaded at one time
#define MAX_DATATABLES 32

class DataManager;

class DataRef
{
	friend class DataManager;

	uint16_t datatableID;
public:
	DataRef();
	DataRef(uint16_t dataID);
	DataRef(Datatable* fontData, uint16_t fontID);
	DataRef(const DataRef& other);

	~DataRef();

	Datatable* datatable;

	Datatable* operator->() { return this->datatable; };
	const Datatable* operator->() const { return this->datatable; };

	bool IsNull();
};

struct DataSlot
{
	Datatable* data;
	uint16_t slotID;
	uint16_t refCount;

	DataSlot();

	void DeleteDatatable();
};

class DataManager
{
	friend class DataRef;

	static DataSlot slots[MAX_DATATABLES];
	static std::string slotNames[MAX_DATATABLES];

	static uint16_t nextAvailibleSlot;

	static void OnDatatableDeleted(uint16_t slotIndex);

	static void FindNextAvailibleSlot();
public:
	static void Init();

	static DataRef GetData(const std::string& str);

	static DataRef LoadData(const std::string& str);

	static bool IsDataLoaded(const std::string& str);

	static std::string GetNameOfFont(const DataRef& ref);

	static size_t SizeOfLoadedTables();
};