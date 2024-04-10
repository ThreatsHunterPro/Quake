#pragma once
#include "../UComponent.h"
#include "reactphysics3d/reactphysics3d.h"
#include "../../../../Runtime/Core/Math/FVector/TVector.h"

using namespace reactphysics3d;

class URigidBody : public UComponent
{
    BoxShape* box;
    Quaternion rotation;
    Transform* transform = nullptr;
    RigidBody* rigidBody = nullptr;

    float timeStep = 1.0f / 60.0f;

public:
    URigidBody(FVector _position, const Quaternion _rotation);

public:
    virtual void Start()override;
    virtual void Update(float _deltaTime)override;
    virtual void Stop()override;

    FORCEINLINE FVector GetPosition()
    {
        return rigidBody->getTransform().getPosition();
    }

    FORCEINLINE void SetMass(float _mass)
    {
        rigidBody->setMass(_mass);
    }

};