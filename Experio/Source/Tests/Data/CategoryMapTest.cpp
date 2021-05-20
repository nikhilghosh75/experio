#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Data/CategoryMap.h"

TEST_SUITE("CategoryMap", "Experio/Data");

UNIT_TEST(TestCategoryMapGeneral, "CategoryMap")
{
	CategoryMap<int> map;
	map.Insert("Rendering/Mesh Component", 101);
	map.Insert("Rendering/Particle Component", 102);

	map.Insert("UI/Text Component", 104);
	map.Insert("UI/Progress Bar", 112);

	map.Insert("Spaceship", 1024);

	ASSERT_EQUAL(map.Count(), 5, "");
	
	TEST_END();
}