#include "APointLight.h"

APointLight::APointLight(const vec3& _color, const vec3& _position, const PointLightDistance& _distance)
	: ALight(_color, _position)
{
	distance = static_cast<int>(_distance);
	UpdatePointLightSettings(_distance);
}

APointLight::APointLight(const vec3& _color, const vec3& _position, const float _distance, const float _linear, const float _quadratic)
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

	lighting.SetFloat("light.constant", constant);
	lighting.SetFloat("light.linear", linear);
	lighting.SetFloat("light.quadratic", quadratic);
}
