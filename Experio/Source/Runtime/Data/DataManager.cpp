#include "DataManager.h"
#include "../Files/Data/DataReader.h"

DataSlot DataManager::slots[MAX_DATATABLES];
std::string DataManager::slotNames[MAX_DATATABLES];
uint16_t DataManager::nextAvailibleSlot;

static uint16_t fontsAllocated;

DataRef::DataRef()
{
	this->datatable = nullptr;
	this->datatableID = MAX_DATATABLES;
}

DataRef::DataRef(uint16_t fontID)
{
	this->datatableID = fontID;
	this->datatable = DataManager::slots[fontID].data;

	DataManager::slots[fontID].refCount++;
}

DataRef::DataRef(Datatable* fontData, uint16_t fontID)
{
	this->datatableID = fontID;
	this->datatable = fontData;

	DataManager::slots[fontID].refCount++;
}

DataRef::DataRef(const DataRef & other)
{
	this->datatableID = other.datatableID;
	this->datatable = other.datatable;

	DataManager::slots[this->datatableID].refCount++;
}

DataRef::~DataRef()
{
	DataManager::OnDatatableDeleted(this->datatableID);
}

bool DataRef::IsNull()
{
	return this->datatable == nullptr || this->datatableID >= MAX_DATATABLES;
}

DataSlot::DataSlot()
{
	this->data = nullptr;
	this->slotID = fontsAllocated;
	this->refCount = 0;

	fontsAllocated++;
}

void DataSlot::DeleteDatatable()
{
	if (this->data != nullptr)
	{
		delete this->data;
		this->data = nullptr;
	}
}

void DataManager::OnDatatableDeleted(uint16_t slotIndex)
{
	if (slotIndex >= MAX_DATATABLES) return;
	DataSlot& slot = slots[slotIndex];

	slot.refCount--;
	if (slot.refCount == 0)
	{
		slot.DeleteDatatable();
		slotNames[slotIndex] = "";
		if (nextAvailibleSlot > slotIndex)
		{
			nextAvailibleSlot = slotIndex;
		}
	}
}

void DataManager::FindNextAvailibleSlot()
{
	for (int i = 0; i < MAX_DATATABLES; i++)
	{
		if (slots[i].data == nullptr && slots[i].refCount <= 0)
		{
			nextAvailibleSlot = i;
			return;
		}
	}
}

void DataManager::Init()
{
	for (int i = 0; i < MAX_DATATABLES; i++)
	{
		slotNames[i] = "";
	}
}

DataRef DataManager::GetData(const std::string & str)
{
	for (uint16_t i = 0; i < MAX_DATATABLES; i++)
	{
		if (str == slotNames[i])
		{
			return DataRef(i);
		}
	}
	return DataRef(nullptr, MAX_DATATABLES);
}

DataRef DataManager::LoadData(const std::string & str)
{
	for (uint16_t i = 0; i < MAX_DATATABLES; i++)
	{
		if (str == slotNames[i])
		{
			return DataRef(i);
		}
	}

	if (slots[nextAvailibleSlot].data != nullptr)
	{
		FindNextAvailibleSlot();
	}

	slotNames[nextAvailibleSlot] = str;
	slots[nextAvailibleSlot].data = DataReader::ReadFile(str.c_str());
	slots[nextAvailibleSlot].refCount++;
	uint16_t lastAvailibleSlot = nextAvailibleSlot;
	FindNextAvailibleSlot();
	return DataRef(lastAvailibleSlot);
}

bool DataManager::IsDataLoaded(const std::string & str)
{
	for (uint16_t i = 0; i < MAX_DATATABLES; i++)
	{
		if (str == slotNames[i])
		{
			return true;
		}
	}
	return false;
}

std::string DataManager::GetNameOfFont(const DataRef & ref)
{
	return slotNames[ref.datatableID];
}
