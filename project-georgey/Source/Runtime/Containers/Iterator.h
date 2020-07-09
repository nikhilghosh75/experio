#pragma once

template<class Container, class Element>
class TIterator
{
public:
	Container& container;
	Element& current;

	operator==(const TIterator<Container, Element>& other)
	{
		return current == other.current && container == other.container;
	}

	operator!=(const TIterator<Container, Element>& other)
	{
		return current != other.current || container != other.container;
	}
};

template<class Container, class Element>
class TForwardIterator : TIterator<Container, Element>
{
public:
	virtual bool IsAtEnd() { return false; }

	virtual operator++() {}
};

template <class Container, class Element>
class TBidirectionalIterator : TForwardIterator<Container, Element>
{
public:
	virtual bool IsAtBegining() { return false; }

	virtual operator--() {};
};

template<class Container, class Element>
class TRandomAccessIterator : TBidirectionalIterator<Container, Element>
{
public:
	virtual operator+=(const int n) {};
	virtual operator-=(const int n) {};
};