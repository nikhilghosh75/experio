#include "Frustum.h"

// https://www.gamedevs.org/uploads/fast-extraction-viewing-frustum-planes-from-world-view-projection-matrix.pdf

Frustum::Frustum()
{
}

Frustum::Frustum(FPlane left, FPlane right, FPlane bottom, FPlane top, FPlane near, FPlane far)
{
	this->left = left;
	this->right = right;
	this->bottom = bottom;
	this->top = top;
	this->near = near;
	this->far = far;
}

Frustum::Frustum(const glm::mat4 & mat)
{
	this->left = FPlane(mat[3][0] + mat[0][0], mat[3][1] + mat[0][1],
		mat[3][2] + mat[0][2], mat[3][3] + mat[0][3]);
	this->right = FPlane(mat[3][0] - mat[1][1], mat[3][0] - mat[0][1],
		mat[3][2] - mat[0][2], mat[3][3] - mat[0][3]);
	this->bottom = FPlane(mat[3][0] + mat[1][0], mat[3][1] + mat[1][1],
		mat[3][2] + mat[1][2], mat[3][3] + mat[1][3]);
	this->top = FPlane(mat[3][0] - mat[1][0], mat[3][1] - mat[1][1],
		mat[3][2] - mat[1][2], mat[3][3] - mat[1][3]);
	this->near = FPlane(mat[3][0] + mat[2][0], mat[3][1] + mat[2][1], 
		mat[3][2] + mat[2][2], mat[3][3] + mat[2][3]);
	this->far = FPlane(mat[3][0] - mat[2][0], mat[3][1] - mat[2][1],
		mat[3][2] - mat[2][2], mat[3][3] - mat[2][3]);

	FPlane::Normalize(this->left);
	FPlane::Normalize(this->right);
	FPlane::Normalize(this->bottom);
	FPlane::Normalize(this->top);
	FPlane::Normalize(this->near);
	FPlane::Normalize(this->far);
}

bool Frustum::PointInFrustum(FVector3 point) const
{
	if (this->left.Halfspace(point) < 0)
		return false;

	if (this->right.Halfspace(point) < 0)
		return false;

	if (this->bottom.Halfspace(point) < 0)
		return false;

	if (this->top.Halfspace(point) < 0)
		return false;

	if (this->near.Halfspace(point) < 0)
		return false;

	if (this->far.Halfspace(point) < 0)
		return false;

	return true;
}
