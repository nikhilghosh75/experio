#include "THashtable.h"
#include <string>
#include "../Debug/Debug.h"
#include "../Debug/TempProfiler.h"

void THashtableTest()
{
	PROFILE_SCOPE("Hashtable Test");

	THashtable<std::string, int, StringHashFunction> populations;
	populations.Insert("New York", 8337);
	populations.Insert("Los Angeles", 3980);
	populations.Insert("Chicago", 2694);
	populations.Insert("Houston", 2320);
	populations.Insert("Phoenix", 1681);
	populations.Insert("San Francisco", 882);

	int tempValue;

	int newYork = populations.Get("New York");
	bool chicago = populations.SafeGet("Chicago", newYork);
	bool seattle = populations.SafeGet("Seattle", tempValue);

	populations.RemoveValue(1681);
	bool phoenix = populations.SafeGet("Phoenix", tempValue);

	std::string testFind;
	bool found = populations.Find(882, testFind);

	Debug::Log("Hashtable Count: " + std::to_string(populations.GetSize()));
}