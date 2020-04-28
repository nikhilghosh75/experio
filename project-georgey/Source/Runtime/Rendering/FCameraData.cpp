#include "FCameraData.h"

FCameraData::FCameraData()
{
	this->fieldOfView = 90.f;
	this->upVector = FVector3(0, 1, 0);
}

FCameraData::FCameraData(float fieldOfView)
{
	this->fieldOfView = fieldOfView;
	this->upVector = FVector3(0, 1, 0);
}

FCameraData::FCameraData(FTransform cameraTransform, float fieldOfView)
{
	this->cameraTransform = cameraTransform;
	this->fieldOfView = fieldOfView;
	this->upVector = FVector3(0, 1, 0);
}

FCameraData::FCameraData(FVector3 position, FQuaternion rotation, float fieldOfView)
{
	this->cameraTransform = FTransform(position, rotation);
	this->fieldOfView = fieldOfView;
	this->upVector = FVector3(0, 1, 0);
}
