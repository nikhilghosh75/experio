#include "Testing\UnitTestingFramework.h"
#include "Components/Spaceship.h"

TEST_SUITE("Spaceship", "Demo Project");

UNIT_TEST(TestSpaceshipPower, "Spaceship")
{
	ASSERT_ALMOST_EQUAL(Spaceship::CalculateAcceleration(10, 0.5), 200);
	ASSERT_ALMOST_EQUAL(Spaceship::CalculateAcceleration(10, 0.1), 100);

	TEST_END();
}