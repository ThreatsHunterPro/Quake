#pragma once
#include "../ALight.h"
#include <map>

enum PointLightDistance
{
    SEPT = 7,
    TREIZE = 13,
    VINGT = 20,
    TRENTE_DEUX = 32,
    CINQUANTE = 50,
    SOIXANTE_CINQ = 65,
    CENT = 100,
    CENT_SOIXANTE = 160,
    DEUX_CENTS = 200,
    TROIS_CENT_VINGT_CINQ = 325,
    SIX_CENTS = 600,
    TROIS_MILLE_DEUX_CENT_CINQUANTE = 3250
};

struct PointLightSettings
{
    float linear;
    float quadratic;

    PointLightSettings() = default;
    PointLightSettings(const float _linear, const float _quadratic)
    {
        linear = _linear;
        quadratic = _quadratic;
    }
};

class APointLight : public ALight
{
    float distance;
    float constant = 1.f;
    float linear;
    float quadratic;

    map<PointLightDistance, PointLightSettings> pointLightSetup =
    {
        { PointLightDistance::SEPT, PointLightSettings(0.7f, 1.8f) },
        { PointLightDistance::TREIZE, PointLightSettings(0.35f, 0.44f) },
        { PointLightDistance::VINGT, PointLightSettings(0.22f, 0.20f) },
        { PointLightDistance::TRENTE_DEUX, PointLightSettings(0.14f, 0.07f) },
        { PointLightDistance::CINQUANTE, PointLightSettings(0.09f, 0.032f) },
        { PointLightDistance::SOIXANTE_CINQ, PointLightSettings(0.07f, 0.017f) },
        { PointLightDistance::CENT, PointLightSettings(0.045f, 0.0075f) },
        { PointLightDistance::CENT_SOIXANTE, PointLightSettings(0.027f, 0.0028f) },
        { PointLightDistance::DEUX_CENTS, PointLightSettings(0.022f, 0.0019f) },
        { PointLightDistance::TROIS_CENT_VINGT_CINQ, PointLightSettings(0.014f, 0.0007f) },
        { PointLightDistance::SIX_CENTS, PointLightSettings(0.007f, 0.0002f) },
        { PointLightDistance::TROIS_MILLE_DEUX_CENT_CINQUANTE, PointLightSettings(0.0014f, 0.000007f) },
    };

public:
    FORCEINLINE float GetConstant() const
    {
        return constant;
    }
    FORCEINLINE float GetLinear() const
    {
        return linear;
    }
    FORCEINLINE float GetQuadratic() const
    {
        return quadratic;
    }

public:
    APointLight() = default;
    APointLight(const FVector& _color, const FVector& _position, const PointLightDistance& _distance);
    APointLight(const FVector& _color, const FVector& _position, const float _distance, const float _linear, const float _quadratic);

private:
    void UpdatePointLightSettings(const PointLightDistance& _distance);

public:
    void Update(const int _index);
};