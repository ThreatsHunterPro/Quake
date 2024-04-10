#include "ALight.h"
#include "../../../../Editor/Engine/Shader/CustomShader.h"

ALight::ALight(const FVector& _color, const FVector& _position)
{
	color = _color;
	position = _position;
	direction = FVector(0, 0, -1);
	lighting = CustomShader();
	ambient = FVector(0.1f);
	diffuse = FVector(0.5f);
	specular = FVector(1.0f);
	intensity = 1.0f;
}

ALight::ALight(const FVector & _color, const FVector & _position, const FVector & _ambient, const FVector & _diffuse, const FVector & _specular)
{
	color = _color;
	position = _position;
	direction = FVector(0, 0, -1);
	lighting = CustomShader();
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	intensity = 1.0f;
}

ALight::ALight(const FVector& _color, const FVector& _position, const FVector& _ambient, const FVector& _diffuse, const FVector& _specular, const float _intensity)
{
	color = _color;
	position = _position;
	direction = FVector(0, 0, -1);
	lighting = CustomShader();
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
	intensity = _intensity;
}

void ALight::SetPhong(const FVector& _ambient, const FVector& _diffuse, const FVector& _specular)
{
	ambient = _ambient;
	diffuse = _diffuse;
	specular = _specular;
}

void ALight::SetShader(const CustomShader& _shader)
{
	lighting = _shader;
}

void ALight::Update(const int _index)
{
	/*ambient *= intensity;
	diffuse *= intensity;
	specular *= intensity;*/
}