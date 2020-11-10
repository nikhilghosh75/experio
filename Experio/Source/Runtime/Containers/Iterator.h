#pragma once

template<typename Container, typename Element>
class TIterator
{
public:
	Container& container;
	Element& current;

	bool operator==(const TIterator<Container, Element>& other)
	{
		return current == other.current && container == other.container;
	}

	bool operator!=(const TIterator<Container, Element>& other)
	{
		return current != other.current || container != other.container;
	}
};

template<typename Container, typename Element>
class TForwardIterator : public TIterator<Container, Element>
{
public:
	virtual bool IsAtEnd() { return false; }

	virtual void Increment() {}
};

template<typename Container, typename Element>
class TBidirectionalIterator : public TForwardIterator<Container, Element>
{
public:
	virtual bool IsAtBegining() { return false; }

	virtual TBidirectionalIterator<Container, Element> operator--() {};
};

template<typename Container, typename Element>
class TRandomAccessIterator : public TBidirectionalIterator<Container, Element>
{
public:
	virtual TRandomAccessIterator<Container, Element> operator+=(const int n) {};
	virtual TRandomAccessIterator<Container, Element> operator-=(const int n) {};
};