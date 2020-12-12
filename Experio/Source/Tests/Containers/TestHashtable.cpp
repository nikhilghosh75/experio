#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Containers/THashtable.h"

TEST_SUITE("Hashtable", "Experio/Containers");

UNIT_TEST(TestHashtableGeneral, "Hashtable")
{
	THashtable<std::string, int, StringHashFunction> populations;
	populations.Insert("New York", 8337);
	populations.Insert("Los Angeles", 3980);
	populations.Insert("Chicago", 2694);
	populations.Insert("Houston", 2320);
	populations.Insert("Phoenix", 1681);
	populations.Insert("San Francisco", 882);

	ASSERT_EQUAL(populations.GetSize(), 7, "");

	int tempValue;

	int newYork = populations.Get("New York");
	ASSERT_EQUAL(newYork, 8337, "Get does not work");

	bool chicago = populations.SafeGet("Chicago", tempValue);
	ASSERT_TRUE(chicago, "");
	ASSERT_EQUAL(tempValue, 2694, "");

	bool seattle = populations.SafeGet("Seattle", tempValue);
	ASSERT_FALSE(seattle, "");

	bool phoenix = populations.SafeGet("Phoenix", tempValue);
	ASSERT_TRUE(phoenix, "");
	populations.RemoveValue(1681);
	phoenix = populations.SafeGet("Phoenix", tempValue);
	ASSERT_FALSE(phoenix, "");
	ASSERT_EQUAL(populations.GetSize(), 6, "");

	TEST_END();
}

UNIT_TEST(TestHashtableLarge, "Hashtable")
{
	THashtable<std::string, int, StringHashFunction> populations;

	populations.Insert("New York", 8337);
	populations.Insert("Los Angeles", 3980);
	populations.Insert("Chicago", 2694);
	populations.Insert("Houston", 2320);
	populations.Insert("Phoenix", 1681);
	populations.Insert("San Francisco", 882);
	populations.Insert("Philadelphia", 1584);
	populations.Insert("San Antonio", 1547);
	populations.Insert("San Diego", 1424);
	populations.Insert("Dallas", 1344);
	populations.Insert("Austin", 979);
	populations.Insert("Jacksonville", 911);
	populations.Insert("Columbus", 899);
	populations.Insert("Charlotte", 886);
	populations.Insert("Indianapolis", 876);
	populations.Insert("Seattle", 753);
	populations.Insert("Nashville", 670);
	populations.Insert("Detroit", 670);
	populations.Insert("Oklahoma City", 655);

	ASSERT_EQUAL(populations.GetSize(), 19, "");

	int temp;
	ASSERT_EQUAL(populations.Get("Detroit"), 670, "");
	ASSERT_TRUE(populations.SafeGet("Charlotte", temp), "");
	ASSERT_EQUAL(temp, 886, "");
	ASSERT_FALSE(populations.SafeGet("Newark", temp), "");

	int numOverMillion = 0;
	populations.ForEach([&numOverMillion](const std::string& key, const int& value) {
		if (value > 1000) { numOverMillion++; }
	});
	ASSERT_EQUAL(numOverMillion, 9, "");

	TEST_END();
}