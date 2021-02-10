#include "../../ExperioEditor/Source/Testing/UnitTestingFramework.h"
#include "Runtime/Math/FQuaternion.h"

TEST_SUITE("Quaternion", "Experio/Math");

UNIT_TEST(TestQuaternionGeneral, "Quaternion")
{
	FQuaternion q(0, 0, 0, 1);
	ASSERT_ALMOST_EQUAL(q.x, 0);
	ASSERT_ALMOST_EQUAL(q.y, 0);
	ASSERT_ALMOST_EQUAL(q.z, 0);
	ASSERT_ALMOST_EQUAL(q.w, 0);

	glm::quat quat(0.5, 1, 1.5, 2);
	FQuaternion q2(quat);
	ASSERT_ALMOST_EQUAL(q2.w, 0.5f);
	ASSERT_ALMOST_EQUAL(q2.x, 1.f);
	ASSERT_ALMOST_EQUAL(q2.y, 1.5f);
	ASSERT_ALMOST_EQUAL(q2.z, 2.f);

	TEST_END();
}

UNIT_TEST(TestQuaternionMatrix, "Quaternion")
{
	glm::mat4 rotm;
	rotm[0] = glm::vec4(0, 0, 1, 0);
	rotm[1] = glm::vec4(0, 1, 0, 0);
	rotm[2] = glm::vec4(-1, 0, 0, 0);
	rotm[3] = glm::vec4(0, 0, 0, 1);

	FQuaternion q(rotm);

	ASSERT_ALMOST_EQUAL(q.w, 0.7071f);
	ASSERT_ALMOST_EQUAL(q.x, 0);
	ASSERT_ALMOST_EQUAL(q.y, 0.7071f);
	ASSERT_ALMOST_EQUAL(q.z, 0);

	TEST_END();
}

UNIT_TEST(TestQuaternionEuler, "Quaternion")
{
	FVector3 e(0.8f, 0.9f, -0.1f);
	FQuaternion q = FQuaternion::MakeFromEuler(e);

	ASSERT_ALMOST_EQUAL(q.x, 0.3302f);
	ASSERT_ALMOST_EQUAL(q.y, 0.4176f);
	ASSERT_ALMOST_EQUAL(q.z, 0.1277f);
	ASSERT_ALMOST_EQUAL(q.w, 0.8368f);

	FQuaternion q2(0.1f, 0.2f, 0.8366f, 0.5f);
	FVector3 e2 = q2.ToEuler();

	ASSERT_ALMOST_EQUAL(e2.x, -0.255f);
	ASSERT_ALMOST_EQUAL(e2.y, 0.376f);
	ASSERT_ALMOST_EQUAL(e2.z, 2.113f);

	TEST_END();
}