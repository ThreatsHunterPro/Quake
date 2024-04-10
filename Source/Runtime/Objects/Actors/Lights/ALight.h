#pragma once
#include "../AActor.h"
#include "../../../../Editor/Engine/Shader/CustomShader.h"
#include "../../../Core/Math/FVector/TVector.h"
#include "../../../Core/Containers/FString.h"

/// <summary>
/// A base light, inherited from AActor
/// DO NOT USE DIRECTLY : USE CHILDREN CLASS
/// </summary>
class ALight : public AActor
{
protected:
    FVector color;
    FVector ambient;
    FVector diffuse;
    FVector specular;
    float intensity;
    FVector position;
    FVector direction;
    CustomShader* lighting;

public:
    FORCEINLINE void SetColor(const FVector& _color)
    {
        color = _color;
    }
    FORCEINLINE void SetPosition(const FVector& _position)
    {
        position = _position;
    }
    FORCEINLINE void SetDirection(const FVector& _direction)
    {
        direction = _direction;
    }
    FORCEINLINE void SetIntensity(const float _intensity)
    {
        intensity = _intensity;
    }
    FORCEINLINE FVector GetColor() const
    {
        return color;
    }
    FORCEINLINE FVector GetPosition() const
    {
        return position;
    }
    FORCEINLINE FVector GetDirection() const
    {
        return direction;
    }
    FORCEINLINE float GetIntensity() const
    {
        return intensity;
    }

public:
    ALight() = default;
    ALight(const FVector& _color, const FVector& _position);
    ALight(const FVector& _color, const FVector& _position, const FVector& _ambient, const FVector& _diffuse, const FVector& _specular);
    ALight(const FVector& _color, const FVector& _position, const FVector& _ambient, const FVector& _diffuse, const FVector& _specular, const float _intensity);

public:
    void SetPhong(const FVector& _ambient, const FVector& _diffuse, const FVector& _specular);
    void SetShader(CustomShader* _lighting);
    virtual void Update(const int _index);
};