#pragma once

#include "Runtime/Framework/GameObject.h"
#include "../Framework/UndoCommand.h"

class MoveCommand : public UndoCommand
{
public:
	GameObject* gameObject;
	FVector3 moveDelta;

	MoveCommand(GameObject* gameObject, FVector3 moveDelta)
	{
		this->gameObject = gameObject;
		this->moveDelta = moveDelta;
		this->name = "Move GameObject";
	}

	virtual void Execute() override
	{
		gameObject->Translate(moveDelta);
	}

	virtual void Unexecute() override
	{
		gameObject->Translate(-moveDelta);
	}
};

class RotateCommand : public UndoCommand
{
public:
	GameObject* gameObject;
	FQuaternion rotation;

	RotateCommand(GameObject* gameObject, FQuaternion rotation)
	{
		this->gameObject = gameObject;
		this->rotation = rotation;
		this->name = "Rotate GameObject";
	}

	virtual void Execute() override
	{
		gameObject->localRotation *= rotation;
	}

	virtual void Unexecute() override
	{
		gameObject->localRotation /= rotation;
	}
};

class ScaleCommand : public UndoCommand
{
public:
	GameObject* gameObject;
	FVector3 scale;

	ScaleCommand(GameObject* gameObject, FVector3 scale)
	{
		this->gameObject = gameObject;
		this->scale = scale;
		this->name = "Scale GameObject";
	}

	virtual void Execute() override
	{
		gameObject->localScale *= scale;
	}

	virtual void Unexecute() override
	{
		gameObject->localScale /= scale;
	}
};

class AddComponentCommand : public UndoCommand
{
public:
	GameObject* gameObject;
	unsigned int classId;
	bool added;

	AddComponentCommand(GameObject* gameObject, unsigned int classId, bool added = true)
	{
		this->gameObject = gameObject;
		this->classId = classId;
		this->added = added;
		this->name = "Add Component";
	}

	virtual void Execute() override
	{
		if (added)
			gameObject->AddComponentByComponentID(classId);
		else
			gameObject->DeleteComponentByComponentID(classId);
	}

	virtual void Unexecute() override
	{
		if (added)
			gameObject->DeleteComponentByComponentID(classId);
		else
			gameObject->AddComponentByComponentID(classId);
	}
};

class SetTagCommand : public UndoCommand
{
public:
	GameObject* gameObject;
	uint16_t previousTag;
	uint16_t currentTag;

	SetTagCommand(GameObject* gameObject, uint16_t previous, uint16_t current)
	{
		this->gameObject = gameObject;
		this->previousTag = previous;
		this->currentTag = current;
		this->name = "Set Tag";
	}

	virtual void Execute() override
	{
		gameObject->tag = currentTag;
	}

	virtual void Unexecute() override
	{
		gameObject->tag = previousTag;
	}
};

class SetLayerCommand : public UndoCommand
{
public:
	GameObject* gameObject;
	uint8_t previousLayer;
	uint8_t currentLayer;

	SetLayerCommand(GameObject* gameObject, uint8_t previous, uint8_t current)
	{
		this->gameObject = gameObject;
		this->previousLayer = previous;
		this->currentLayer = current;
		this->name = "Set Layer";
	}

	virtual void Execute() override
	{
		gameObject->layer = currentLayer;
	}

	virtual void Unexecute() override
	{
		gameObject->layer = previousLayer;
	}
};

class SetNameCommand : public UndoCommand
{
public:
	GameObject* gameObject;
	std::string previousName;
	std::string currentName;

	SetNameCommand(GameObject* gameObject, std::string previousName, std::string currentName)
	{
		this->gameObject = gameObject;
		this->previousName = previousName;
		this->currentName = currentName;
		this->name = "Set Name";
	}

	virtual void Execute() override
	{
		gameObject->name = currentName;
	}

	virtual void Unexecute() override
	{
		gameObject->name = previousName;
	}
};