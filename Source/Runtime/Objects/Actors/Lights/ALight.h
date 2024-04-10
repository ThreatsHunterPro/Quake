#pragma once
#include "../AActor.h"
#include "../../../../Editor/Engine/Shader/CustomShader.h"
#include "../../../Core/Math/FVector/TVector.h"

class ALight : public AActor
{
protected:
    FVector color;
    FVector position;
    FVector direction;
    CustomShader lighting;

public:
    FORCEINLINE void SetColor(const FVector& _color)
    {
        color = _color;
    }
    FORCEINLINE void SetPosition(const FVector& _position)
    {
        position = _position;
        lighting.SetVec3("light.position", position);
    }
    FORCEINLINE FVector GetColor() const
    {
        return color;
    }
    FORCEINLINE FVector GetPosition() const
    {
        return position;
    }

public:
    ALight() = default;
    ALight(const FVector& _color, const FVector& _position);

public:
    void SetPhong(const FVector& _ambient, const FVector& _diffuse, const FVector& _specular);
    void SetShader(const CustomShader& _shader);
    virtual void Update(const int _index);
};