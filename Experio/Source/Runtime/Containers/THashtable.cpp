#include "THashtable.h"
#include <string>
#include "../Debug/Debug.h"
#include "../Debug/TempProfiler.h"

#define HASHTABLE_START_CAPACITY 8

void THashtableTest()
{
	PROFILE_SCOPE("Hashtable Test");

	THashtable<std::string, int, StringHashFunction> hashtable;
	hashtable.Insert("New York", 100);
	hashtable.Insert("Los Angeles", 75);
	hashtable.Insert("Chicago", 64);
	hashtable.Insert("Detroit", 44);
	hashtable.Insert("San Francisco", 64);

	int newYork = hashtable.Get("New York");
	int seattleValue;
	bool seattle = hashtable.SafeGet("Seattle", seattleValue);

	hashtable.RemoveValue(64);

	Debug::Log("Hashtable Count: " + std::to_string(hashtable.GetSize()));
}