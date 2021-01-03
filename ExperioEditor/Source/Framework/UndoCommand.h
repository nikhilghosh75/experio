#pragma once
#include <string>

class UndoCommand
{
public:
	std::string name;

	virtual void Execute() = 0;
	virtual void Unexecute() = 0;
};


#include "Runtime/Framework/GameObject.h"

class MoveCommand : UndoCommand
{
public:
	GameObject* gameObject;
	FVector3 moveDelta;

	virtual void Execute() override
	{
		gameObject->Translate(moveDelta);
	}

	virtual void Unexecute() override
	{
		gameObject->Translate(-moveDelta);
	}
};

class RotateCommand : UndoCommand
{
public:
	GameObject* gameObject;
	
};