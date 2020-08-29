#pragma once
#include <cstdint>
#include <array>
#include <sstream>
using namespace std;

template <class T> class TElement
{
public:
    T * data;
    TElement<T>* previous;
    TElement<T>* next;
    int count;

    TElement();
    TElement(T elements[], int count, TElement<T>* previous, TElement<T>* next);
    TElement(T elem1, T elem2, T elem3, T elem4, TElement<T>* previous, TElement<T>* next);
    TElement(T elem, int count, TElement<T>* previous, TElement<T>* next);
    
    void SetNext(TElement<T>* newNext);
    int Count();
    T* Get(int i);

    void RemoveAt(int index);
    // TODO: Implement Destructor
};

template <class T> class TArray
{
private:
    TElement<T>* start;
    TElement<T>* end;
    int numElements;
    int count;
public:
    TArray();
    
    void Init(T object, int num);

    void Append(const T object);
    void Append(const T objects[], int count);
    void Append(const TArray<T> objects);

    void Insert(T object, int index);
    void Insert(TArray<T> objects, int index);
    void Insert(T objects[], int count, int index);

    int Num() const;
    int Count() const;
    size_t GetSize() const; 
    bool IsValidIndex(int index) const;

    T& operator[](int i);

    T& First();
    T& Last();

    int Find(T objectToFind);
    bool Find(T objectToFind, int& indexOfObject);
    TArray<int> FindAll(T objectToFind);
    int FindInRange(T objectToFind, int start, int end);
    bool FindInRange(T objectToFind, int& indexOfObject, int start, int end);
    TArray<int> FindAllInRange(T objectToFind, int start, int end);

    bool AddUnique(T object);

    void Empty();

    void Remove(T item);
    void RemoveInRange(T item, int start, int end);
    void RemoveAt(int index);
    void RemoveAt(int index, int count);
    void RemoveSingle(T item);

    T* ToArray() const;
    string ToString() const;

    void Swap(int indexA, int indexB);

    operator string() const {return ToString();}
    //TArray<T> operator+(const TArray<T> array);
    //TArray<T> operator+(const T item);
    //TArray<T> operator+=(const TArray<T> array);
    //TArray<T> operator+=(const T item);
};