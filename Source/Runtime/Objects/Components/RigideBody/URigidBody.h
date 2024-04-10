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

public:
    URigidBody(AActor* _owner, FVector _position, const Quaternion _rotation);

public:
    virtual void Start()override;
    virtual void Update(float _deltaTime)override;
    virtual void Stop()override;


};