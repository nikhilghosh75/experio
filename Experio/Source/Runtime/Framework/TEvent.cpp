#include "TEvent.h"
#include <thread>


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
	std::thread listenerThread(&TEvent::CallListeners, this);
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
void TEventOne<InOne>::CallListeners(InOne a)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i].Call(a);
	}
}

template<class InOne>
void TEventOne<InOne>::Invoke(InOne a)
{
	std::thread listenerThread(&TEventOne::CallListeners, this, a);
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
void TEventTwo<InOne, InTwo>::CallListeners(InOne a, InTwo b)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i].Call(a, b);
	}
}

template<class InOne, class InTwo>
void TEventTwo<InOne, InTwo>::Invoke(InOne a, InTwo b)
{
	std::thread listenerThread(&TEventTwo::CallListeners, this, a, b);
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
void TEventThree<InOne, InTwo, InThree>::CallListeners(InOne a, InTwo b, InThree c)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i].Call(a, b, c);
	}
}

template<class InOne, class InTwo, class InThree>
void TEventThree<InOne, InTwo, InThree>::Invoke(InOne a, InTwo b, InThree c)
{
	std::thread listenerThread(&TEventThree::CallListeners, this, a, b, c);
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
void TEventFour<InOne, InTwo, InThree, InFour>::CallListeners(InOne a, InTwo b, InThree c, InFour d)
{
	for (int i = 0; i < listeners.size(); i++)
	{
		listeners[i].Call(a, b, c, d);
	}
}

template<class InOne, class InTwo, class InThree, class InFour>
void TEventFour<InOne, InTwo, InThree, InFour>::Invoke(InOne a, InTwo b, InThree c, InFour d)
{
	std::thread listenerThread(&TEventFour::CallListeners, this, a, b, c, d);
	listenerThread.detach();
	return;
}
