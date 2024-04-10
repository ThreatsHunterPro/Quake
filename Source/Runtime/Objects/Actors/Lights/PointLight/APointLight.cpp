#include "APointLight.h"

APointLight::APointLight(const FVector& _color, const FVector& _position, const PointLightDistance& _distance)
	: ALight(_color, _position)
{
	distance = static_cast<int>(_distance);
	UpdatePointLightSettings(_distance);
}

APointLight::APointLight(const FVector& _color, const FVector& _position, const float _distance, const float _linear, const float _quadratic)
	: ALight(_color, _position)
{
	distance = _distance;
	linear = _linear;
	quadratic = _quadratic;
}

void APointLight::UpdatePointLightSettings(const PointLightDistance& _distance)
{
	PointLightSettings _settings = pointLightSetup[_distance];
	linear = _settings.linear;
	quadratic = _settings.quadratic;
}

void APointLight::Start(const CustomShader& _lighting)
{
	ALight::Start(_lighting);

	FString _name;
	_name = _name.Format("pointLights[{}].", _index);

	lighting.SetFloat(_name + "constant", constant);
	lighting.SetFloat(_name + "linear", linear);
	lighting.SetFloat(_name + "quadratic", quadratic);
	lighting.SetVec3(_name + "position", position);
	lighting.SetVec3(_name + "ambient", ambient);
	lighting.SetVec3(_name + "diffuse", diffuse);
	lighting.SetVec3(_name + "specular", specular);
}
