#pragma once
#include <vector>
#include <string>

using namespace std;

struct TFunctionPointer
{
	void(*function)();

	TFunctionPointer(void(*newFunction)())
	{
		function = newFunction;
	}

	void Call()
	{ 
		function(); 
	}
};

template <class InOne>
struct TFunctionPointerOne
{
	void(*function)(InOne a);

	TFunctionPointerOne(void(*newFunction)(InOne a))
	{
		function = newFunction;
	}

	void Call(InOne a)
	{
		function(a);
	}
};

template <class InOne, class InTwo>
struct TFunctionPointerTwo
{
	void(*function)(InOne a, InTwo b);

	TFunctionPointerTwo(void(*newFunction)(InOne a, InTwo b))
	{
		function = newFunction;
	}

	void Call(InOne a, InTwo b)
	{
		function(a, b);
	}
};

template <class InOne, class InTwo, class InThree>
struct TFunctionPointerThree
{
	void(*function)(InOne a, InTwo b, InThree c);

	TFunctionPointerThree(void(*newFunction)(InOne a, InTwo b, InThree c))
	{
		function = newFunction;
	}

	void Call(InOne a, InTwo b, InThree c)
	{
		function(a, b, c);
	}
};

template <class InOne, class InTwo, class InThree, class InFour>
struct TFunctionPointerFour
{
	void(*function)(InOne a, InTwo b, InThree c, InFour d);

	TFunctionPointerFour(void(*newFunction)(InOne a, InTwo b, InThree c, InFour d))
	{
		function = newFunction;
	}

	void Call(InOne a, InTwo b, InThree c, InFour d)
	{
		function(a, b, c, d);
	}
};

class TEvent
{
	vector<TFunctionPointer> listeners;
public:
	void AddListener(void(*function)());

	void CallListeners();

	void Invoke();
};

template <class InOne>
class TEventOne
{
	vector<TFunctionPointerOne<InOne>> listeners;
public:
	void AddListener(void(*function)(InOne a));

	void CallListeners(InOne a);

	void Invoke(InOne a);
};

template <class InOne, class InTwo>
class TEventTwo
{
	vector<TFunctionPointerTwo<InOne, InTwo>> listeners;
public:
	void AddListener(void(*function)(InOne a, InTwo b));

	void CallListeners(InOne a, InTwo b);

	void Invoke(InOne a, InTwo b);
};

template <class InOne, class InTwo, class InThree>
class TEventThree
{
	vector<TFunctionPointerThree<InOne, InTwo, InThree>> listeners;
public:
	void AddListener(void(*function)(InOne a, InTwo b, InThree c));

	void CallListeners(InOne a, InTwo b, InThree c);

	void Invoke(InOne a, InTwo b, InThree c);
};

template <class InOne, class InTwo, class InThree, class InFour>
class TEventFour
{
	vector<TFunctionPointerFour<InOne, InTwo, InThree, InFour>> listeners;
public:
	void AddListener(void(*function)(InOne a, InTwo b, InThree c, InFour d));

	void CallListeners(InOne a, InTwo b, InThree c, InFour d);

	void Invoke(InOne a, InTwo b, InThree c, InFour d);
};