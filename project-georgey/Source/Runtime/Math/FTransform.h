#pragma once
#include "FVector3.h"
#include "FQuaternion.h"
#include "../Events/TEvent.h"

struct FTransform
{
private:
	FVector3 position;
	FQuaternion rotation;
	FVector3 scale;

public:
	FTransform();
	FTransform(FVector3 position, FQuaternion rotation);
	FTransform(FVector3 position, FQuaternion rotation, FVector3 scale);

	FVector3 GetPosition() const { return position; }
	FQuaternion GetRotation() const { return rotation; }
	FVector3 GetScale() const { return scale; }

	void SetPosition(FVector3 position);
	void SetRotation(FQuaternion rotation);
	void SetScale(FVector3 scale);

	TEvent OnTransformChange;
	TEventOne<FVector3> OnPositionChange;
	TEventOne<FQuaternion> OnRotationChange;
	TEventOne<FVector3> OnScaleChange;

	void Translate(FVector3 translationAmount);
	void Rotate(FQuaternion rotation);
	void Scale(FVector3 scale);
};