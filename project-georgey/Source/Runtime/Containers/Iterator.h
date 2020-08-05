#pragma once

template<class Container, class Element>
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

template<class Container, class Element>
class TForwardIterator : public TIterator<Container, Element>
{
public:
	virtual bool IsAtEnd() { return false; }

	virtual void Increment() {}
};

template <class Container, class Element>
class TBidirectionalIterator : public TForwardIterator<Container, Element>
{
public:
	virtual bool IsAtBegining() { return false; }

	virtual TBidirectionalIterator<Container, Element> operator--() {};
};

template<class Container, class Element>
class TRandomAccessIterator : public TBidirectionalIterator<Container, Element>
{
public:
	virtual TRandomAccessIterator<Container, Element> operator+=(const int n) {};
	virtual TRandomAccessIterator<Container, Element> operator-=(const int n) {};
};