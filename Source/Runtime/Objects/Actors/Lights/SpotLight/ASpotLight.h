#pragma once
#include "../PointLight/APointLight.h"

/// <summary>
/// A light that works like a streetlight / flashlight
/// </summary>
class ASpotLight : public APointLight
{
	float cutOff;
	float outerCutOff;

public:
    FORCEINLINE float GetCutOff() const
    {
        return cutOff;
    }
    FORCEINLINE float GetOuterCutOff() const
    {
        return outerCutOff;
    }

public:
    ASpotLight() = default;
    ASpotLight(const FVector& _color, const FVector& _position, const PointLightDistance& _distance);
    ASpotLight(const FVector& _color, const FVector& _position, const PointLightDistance& _distance, const float _cutOff, const float _outerCutOff);
    ASpotLight(const FVector& _color, const FVector& _position, const float _distance, const float _linear, const float _quadratic, const float _cutOff, const float _outerCutOff);

private:
    void UpdateSpotLightSettings(const PointLightDistance& _distance, const float _cutOff, const float _outerCutOff);

public:
    void Update(const int _index) override;
};