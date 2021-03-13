#pragma once
#include "Framework.h"
#include "Scene.h"

#define MAX_GAME_OBJECT_DEPTH 32

/// <summary>
/// An iterator over GameObjects. It is very buggy, so it will likely be overhauled later
/// </summary>

class GameObjectIterator
{
	uint8_t position[MAX_GAME_OBJECT_DEPTH];
	bool goDown = false;
	int currentDepth = 0;
	unsigned short nodeVisitedCount = 1;

	GameObject* origin;
public:
	GameObject* current;

	GameObjectIterator(GameObject* object)
	{
		origin = object;
		current = object;

		for (int i = 0; i < MAX_GAME_OBJECT_DEPTH; i++)
		{
			position[i] = 0;
		}
	}
	
	bool IsAtEnd() const 
	{ 
		return origin == current && nodeVisitedCount != 1; 
	}

	void Increment()
	{
		if (this->nodeVisitedCount == 1)
		{
			this->current = this->current->children[0];
			nodeVisitedCount++;
			currentDepth++;
		}
		else if (this->current->children.size() > 0)
		{
			this->current = this->current->children[0];
			currentDepth++;
			position[currentDepth] = 0;
			this->nodeVisitedCount++;
		}
		else
		{
			GameObject* tempCurrent = this->current;
			for (int i = this->currentDepth; i > 0; i--)
			{
				tempCurrent = tempCurrent->parent;
				if (tempCurrent->children.size() > position[i - 1] + 1)
				{
					this->current = tempCurrent->children[position[i - 1] + 1];
					position[i - 1]++;
					this->nodeVisitedCount++;
					return;
				}
			}

			if (position[0] + 1 >= tempCurrent->children.size())
			{
				this->current = tempCurrent;
				return;
			}
			this->current = tempCurrent->children[(position[0] + 1) % tempCurrent->children.size()];
			currentDepth = 0;
			this->nodeVisitedCount++;
		}
	}
};