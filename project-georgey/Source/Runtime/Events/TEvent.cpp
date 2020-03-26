#include "TEvent.h"
#include <thread>

using namespace std;

void TEvent::AddListener(void(*function)())
{
	listeners.emplace_back(function);
}

void TEvent::CallListeners()
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i].Call();
	}
}

void TEvent::Invoke()
{
	CallListeners();
	return;
}
