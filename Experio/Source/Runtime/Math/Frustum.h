#pragma once
#include "FPlane.h"
#include "FVector3.h"
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"

struct Frustum
{
	FPlane left;
	FPlane right;
	FPlane bottom;
	FPlane top;
	FPlane near;
	FPlane far;

	Frustum();

	Frustum(FPlane left, FPlane right, FPlane bottom, FPlane top, FPlane near, FPlane far);

	Frustum(const glm::mat4& mat);

	bool PointInFrustum(FVector3 point) const;
};