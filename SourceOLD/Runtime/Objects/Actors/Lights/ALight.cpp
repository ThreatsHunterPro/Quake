#include "ALight.h"

ALight::ALight(const vec3& _color, const vec3& _position)
{
	color = _color;
	position = _position;
	lighting = CustomShader();
}

void ALight::Start(const CustomShader& _lighting)
{
	lighting = _lighting;
	lighting.SetVec3("light.position", position);
}