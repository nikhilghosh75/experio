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

	void CallListeners();
public:
	void AddListener(void(*function)());

	void Invoke();
};