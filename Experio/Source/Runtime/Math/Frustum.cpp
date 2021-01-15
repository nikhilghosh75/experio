#include "Frustum.h"

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
