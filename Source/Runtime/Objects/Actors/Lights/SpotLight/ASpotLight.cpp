#include "ASpotLight.h"

ASpotLight::ASpotLight(const FVector& _color, const FVector& _position, const PointLightDistance& _distance)
	: APointLight(_color, _position, _distance)
{
	cutOff = 12.5f;
	outerCutOff = 17.5f;
	direction = FVector(0, 0, -1);
}

ASpotLight::ASpotLight(const FVector& _color, const FVector& _position, const PointLightDistance& _distance, const float _cutOff, const float _outerCutOff)
	: APointLight(_color, _position, _distance)
{
	cutOff = _cutOff;
	outerCutOff = _outerCutOff;
	direction = FVector(0, 0, -1);
}

ASpotLight::ASpotLight(const FVector& _color, const FVector& _position, const float _distance, const float _linear, const float _quadratic, const float _cutOff, const float _outerCutOff)
	: APointLight(_color, _position, _distance, _linear, _quadratic)
{
	cutOff = _cutOff;
	outerCutOff = _outerCutOff;
	direction = FVector(0, 0, -1);
}

void ASpotLight::UpdateSpotLightSettings(const PointLightDistance& _distance, const float _cutOff, const float _outerCutOff)
{
	//UpdatePointLightSettings(_distance);
	cutOff = _cutOff;
	outerCutOff = _outerCutOff;
	direction = FVector(0, 0, -1);
}

void ASpotLight::Update(const int _index)
{
	ALight::Update(_index);

	FString _name;
	_name = _name.Format("spotLights[{}].", _index);

	lighting.SetFloat(_name + "cutOff", cutOff);
	lighting.SetFloat(_name + "outerCutOff", outerCutOff);
	lighting.SetVec3(_name + "direction", direction);
	lighting.SetVec3(_name + "position", position);
			
	//lighting.SetFloat(_name + "constant", constant);
	//lighting.SetFloat(_name + "linear", linear);
	//lighting.SetFloat(_name + "quadratic", quadratic);
			
	lighting.SetVec3(_name + "ambient", ambient);
	lighting.SetVec3(_name + "diffuse", diffuse);
	lighting.SetVec3(_name + "specular", specular);
}
