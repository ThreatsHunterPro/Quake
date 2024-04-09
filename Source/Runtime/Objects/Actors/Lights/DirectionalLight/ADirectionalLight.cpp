#include "ADirectionalLight.h"

ADirectionalLight::ADirectionalLight(const FVector& _color)
	: ALight(_color, FVector::ZeroVector)
{
	direction = FVector(0, 0, -1);
}

ADirectionalLight::ADirectionalLight(const FVector& _color, const FVector& _direction)
	: ALight(_color, FVector::ZeroVector)
{
	direction = _direction;
}

void ADirectionalLight::Update(const int _index)
{
	ALight::Update(_index);

	FString _name;
	_name = _name.Format("dirLights[{}].", _index);

	lighting.SetVec3(_name + "direction", direction);
	lighting.SetVec3(_name + "ambient", ambient);
	lighting.SetVec3(_name + "diffuse", diffuse);
	lighting.SetVec3(_name + "specular", specular);
}
