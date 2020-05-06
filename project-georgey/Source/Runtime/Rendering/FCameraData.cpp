#include "FCameraData.h"

FCameraData::FCameraData()
{
	this->fieldOfView = 90.f;
}

FCameraData::FCameraData(float fieldOfView)
{
	this->fieldOfView = fieldOfView;
}

FCameraData::FCameraData(FTransform cameraTransform, float fieldOfView)
{
	this->cameraTransform = cameraTransform;
	this->fieldOfView = fieldOfView;
}

FCameraData::FCameraData(FVector3 position, FQuaternion rotation, float fieldOfView)
{
	this->cameraTransform = FTransform(position, rotation);
	this->fieldOfView = fieldOfView;
}
