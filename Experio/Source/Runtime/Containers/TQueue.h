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

	TQueue(T* objects, size_t count)
	{
		this->head = new TQueueNode<T>(objects[0]);
		TQueueNode<T>* current = head;
		for (int i = 1; i < count; i++)
		{
			this->tail = new TQueueNode<T>(objects[i]);
			current->next = this->tail;
			current = current->next;
		}
		this->count = count;
	}

	TQueue(std::vector<T> objects)
	{
		this->head = new TQueueNode<T>(objects[0]);
		TQueueNode<T>* current = head;
		for (int i = 1; i < objects->size(); i++)
		{
			this->tail = new TQueueNode<T>(objects[i]);
			current->next = this->tail;
			current = current->next;
		}
		this->count = objects->size();
	}

	~TQueue()
	{
		TQueueNode<T>* current = head;
		for (int i = 0; i < count; i++)
		{
			TQueueNode<T>* tempCurrent = current;
			current = current->next;
			delete tempCurrent;
		}
	}

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
				Debug::LogError("Index " + std::to_string(index) + " is out of range");
				return current->object;
			}
			current = current->next;
		}
		return current->object;
	}

	T Pop()
	{
		T object = head->object;
		TQueueNode<T>* newHead = this->head->next;
		delete this->head;
		this->head = newHead;
		this->count--;
	}

	void Push(T object)
	{
		TQueueNode<T>* newTail = new TQueueNode<T>(object);
		if (this->tail != nullptr)
		{
			this->tail->next = newTail;
		}
		this->tail = newTail;
		
		if (this->head == nullptr)
		{
			this->head = newTail;
		}

		this->count++;
	}

	template<typename ... Args>
	T& EmplacePush(Args&& ... args)
	{
		TQueueNode<T>* newTail = new TQueueNode<T>(T(std::forward<Args>(Args) ...));
		if (this->tail != nullptr)
		{
			this->tail->next = newTail;
		}
		this->tail = newTail;

		if (this->head == nullptr)
		{
			this->head = newTail;
		}

		this->count++;
	}

	void Empty()
	{
		TQueueNode<T>* current = head;
		for (int i = 0; i < count; i++)
		{
			TQueueNode<T>* tempCurrent = current;
			current = current->next;
			delete tempCurrent;
		}
		this->count = 0;
	}
	
	bool IsEmpty() const { return this->count == 0; }

	unsigned int Count() const { return count; }
};