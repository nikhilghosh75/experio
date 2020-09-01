#pragma once
#include <vector>
#include "../Debug/Debug.h"

template<class T>
struct TQueueNode
{
	T object;
	TQueueNode<T>* next;

	TQueueNode()
	{
		this->next = nullptr;
	}

	TQueueNode(T object, TQueueNode<T>* next)
	{
		this->object = object;
		this->next = nullptr;
	}
};

template<class T>
class TQueue
{
	TQueueNode<T>* head; // Remove here
	TQueueNode<T>* tail; // Add here

	unsigned int count = 0;
public:
	TQueue()
	{
		head = nullptr;
		tail = nullptr;
		count = 0;
	}

	TQueue(T headObject)
	{
		head = new TQueueNode<T>(headObject);
		tail = nullptr;
		count = 1;
	}

	TQueue(T headObject, T tailObject)
	{
		head = new TQueueNode<T>(headObject);
		tail = new TQueueNode<T>(tailObject);
		head->next = tail;
		count = 2;
	}

	TQueue(T* objects, size_t count);
	TQueue(std::vector<T> objects);

	~TQueue();

	T& Peek() const
	{
		return head->object;
	}

	T& PeekAt(unsigned int index) const
	{
		TQueueNode<T>* current = head;
		for (int i = 0; i < index; i++)
		{
			if (current->next == nullptr)
			{
				Debug::LogError("Index " + to_string(index) + " is out of range");
				return current->object;
			}
			current = current->next;
		}
		return current->object;
	}

	T Pop();

	void Push(T object);

	unsigned int GetCount() const { return count; }
};