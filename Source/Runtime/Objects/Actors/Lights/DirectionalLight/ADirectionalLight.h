#pragma once
#include "../PointLight/APointLight.h"

/// <summary>
/// A light that works like the sun
/// </summary>
class ADirectionalLight : public ALight
{
public:
	ADirectionalLight() = default;
	ADirectionalLight(const FVector& _color);
	ADirectionalLight(const FVector& _color, const FVector& _direction);

public:
	void Update(const int _index) override;
};