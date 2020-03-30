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
	thread listenerThread(&TEvent::CallListeners, this);
	listenerThread.detach();
	return;
}

// TEventOne

template<class InOne>
inline void TEventOne<InOne>::AddListener(void(*function)(InOne a))
{
	listeners.emplace_back(function);
}

template<class InOne>
void TEventOne<InOne>::CallListeners()
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i].Call();
	}
}

template<class InOne>
void TEventOne<InOne>::Invoke()
{
	thread listenerThread(&TEventOne::CallListeners, this);
	listenerThread.detach();
	return;
}

// TEventTwo

template<class InOne, class InTwo>
inline void TEventTwo<InOne, InTwo>::AddListener(void(*function)(InOne a, InTwo b))
{
	listeners.emplace_back(function);
}

template<class InOne, class InTwo>
void TEventTwo<InOne, InTwo>::CallListeners()
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i].Call();
	}
}

template<class InOne, class InTwo>
void TEventTwo<InOne, InTwo>::Invoke()
{
	thread listenerThread(&TEventTwo::CallListeners, this);
	listenerThread.detach();
	return;
}

// TEventThree

template<class InOne, class InTwo, class InThree>
inline void TEventThree<InOne, InTwo, InThree>::AddListener(void(*function)(InOne a, InTwo b, InThree c))
{
	listeners.emplace_back(function);
}

template<class InOne, class InTwo, class InThree>
void TEventThree<InOne, InTwo, InThree>::CallListeners()
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i].Call();
	}
}

template<class InOne, class InTwo, class InThree>
void TEventThree<InOne, InTwo, InThree>::Invoke()
{
	thread listenerThread(&TEventThree::CallListeners, this);
	listenerThread.detach();
	return;
}

// TEventFour

template<class InOne, class InTwo, class InThree, class InFour>
inline void TEventFour<InOne, InTwo, InThree, InFour>::AddListener(void(*function)(InOne a, InTwo b, InThree c, InFour d))
{
	listeners.emplace_back(function);
}

template<class InOne, class InTwo, class InThree, class InFour>
void TEventFour<InOne, InTwo, InThree, InFour>::CallListeners()
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i].Call();
	}
}

template<class InOne, class InTwo, class InThree, class InFour>
void TEventFour<InOne, InTwo, InThree, InFour>::Invoke()
{
	thread listenerThread(&TEventFour::CallListeners, this);
	listenerThread.detach();
	return;
}
