#include "TArray.h"
#include <iostream>
#include <exception>

void TestArray()
{
	TArray<int> array(125, 5);

	// Check Count
	std::cout << array.Count() << std::endl; // 5

	// Check Access Function
	array[3] = 6;
	std::cout << array[3] << std::endl; // 6
	std::cout << array[4] << std::endl; // 125

	// Check Object Append
	array.Append(64);
	std::cout << array[5] << std::endl; // 64

	// Check Array Append
	int tempArray[2];
	tempArray[0] = 12;
	tempArray[1] = 13;
	array.Append(tempArray, 2);
	std::cout << array[7] << std::endl; // 13

	// Check Array Insert
	array.Insert(256, 5);
	std::cout << array[5] << std::endl; // 256
	std::cout << array.Count() << std::endl; // 9

	// Check First
	std::cout << array.First() << std::endl; // 125

	// Check Last
	std::cout << array.Last() << std::endl; // 13

	// Find
	std::cout << array.FindIndex(6) << std::endl; // 3
	std::cout << array.FindIndex(1) << std::endl; // Numeric Limits

	// FindAll
	array.Append(343);
	TArray<uint32_t> foundArray = array.FindAll(343);
	std::cout << foundArray.Count() << std::endl; // 1

	// RemoveAt
	array.RemoveAt(3);
	std::cout << array[3] << std::endl; // 125
	std::cout << array.Count() << std::endl; // 16

	// Remove
	array.Remove(343);
	std::cout << array.FindAll(343).Count() << std::endl; // 0

	// Swap
	array.Swap(0, 7);
	std::cout << array[0] << std::endl; // 13

	// Plus
	//array += testArray;
	//cout << array.Count() << endl;
}