#pragma once
#include "../AActor.h"
#include "../../../Managers/CustomShader.h"

class ALight : public AActor
{
protected:
    vec3 color;
    vec3 position;
    CustomShader lighting;

public:
    FORCEINLINE void SetColor(const vec3& _color)
    {
        color = _color;
    }
    FORCEINLINE void SetPosition(const vec3& _position)
    {
        position = _position;
        lighting.SetVec3("light.position", position);
    }
    FORCEINLINE vec3 GetColor() const
    {
        return color;
    }
    FORCEINLINE vec3 GetPosition() const
    {
        return position;
    }

public:
    ALight() = default;
    ALight(const vec3& _color, const vec3& _position);

public:
    virtual void Start(const CustomShader& _lighting);
};