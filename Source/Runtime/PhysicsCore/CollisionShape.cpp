#include "CollisionShape.h"
#include "../Core/Math/FVector/TVector.h"
#include "../../Editor/Engine/Engine.h"
#include "../Classes/World/UWorld.h"

FCollisionShape::FCollisionShape()
{
    //ShapeType = ECollisionShape::Line;
    Box.Shape = Engine::GetInstance().GetWorld()->GetPhysics().createBoxShape(Vector3());
    //Sphere.Shape = UWorld::GetPhysics().createSphereShape(0);
    //Capsule.Shape = UWorld::GetPhysics().createCapsuleShape(0, 0);
}

FCollisionShape::FCollisionShape(const FCollisionShape& _copy) : FCollisionShape()
{
    ShapeType = _copy.ShapeType;

    switch (ShapeType)
    {
    case ECollisionShape::Box:
        Box = _copy.Box;
        break;
    case  ECollisionShape::Sphere:
        Sphere = _copy.Sphere;
        break;
    case ECollisionShape::Capsule:
        Capsule = _copy.Capsule;
        break;
    }
}

#pragma region Getter
FVector FCollisionShape::GetBox() const
{
    return FVector(Box.Shape->getHalfExtents());
}

float FCollisionShape::GetCapsuleAxisHalfLength() const
{
    if (ShapeType == ECollisionShape::Capsule)
        return FMath::Max<float>(Capsule.Shape->getHeight() / 2 - Capsule.Shape->getRadius(), FCollisionShape::FCollisionShape::MinCapsuleAxisHalfHeight());
    return 0.0f;
}

const float FCollisionShape::GetCapsuleHalfHeight() const
{
    return Capsule.Shape->getHeight() / 2;
}

const float FCollisionShape::GetCapsuleRadius() const
{
    return Capsule.Shape->getRadius();
}

FVector FCollisionShape::GetExtent() const
{
    switch (ShapeType)
    {
    case ECollisionShape::Box:
        return FVector(Box.Shape->getHalfExtents());
        break;
    case  ECollisionShape::Sphere:
        return FVector(Sphere.Shape->getRadius(), Sphere.Shape->getRadius(), Sphere.Shape->getRadius());
        break;
    case ECollisionShape::Capsule:
        return FVector(Capsule.Shape->getRadius(), Capsule.Shape->getRadius(), Capsule.Shape->getHeight() / 2);
        break;
    }
    return FVector::ZeroVector;
}

const float FCollisionShape::GetSphereRadius() const
{
    return Sphere.Shape->getRadius();
}
#pragma endregion

#pragma region Checks
bool FCollisionShape::IsBox() const
{
    return ShapeType == ECollisionShape::Box;
}

bool FCollisionShape::IsCapsule() const
{
    return ShapeType == ECollisionShape::Capsule;
}

bool FCollisionShape::IsLine() const
{
    return ShapeType == ECollisionShape::Line;
}

bool FCollisionShape::IsNearlyZero() const
{
    switch (ShapeType)
    {
        case ECollisionShape::Box:
            return (Box.Shape->getHalfExtents().x <= FCollisionShape::MinBoxExtent() && Box.Shape->getHalfExtents().y <= FCollisionShape::MinBoxExtent() && Box.Shape->getHalfExtents().z <= FCollisionShape::MinBoxExtent());
            break;
        case  ECollisionShape::Sphere:
            return (Sphere.Shape->getRadius() <= FCollisionShape::MinSphereRadius());
            break;
        case ECollisionShape::Capsule:
            // @Todo check height? It didn't check before, so I'm keeping this way for time being
            return (Capsule.Shape->getRadius() <= FCollisionShape::MinCapsuleRadius());
            break;
    }
    return true;
}

bool FCollisionShape::IsSphere() const
{
    return ShapeType == ECollisionShape::Sphere;
}
#pragma endregion

#pragma region Make
FCollisionShape FCollisionShape::MakeBox(const FVector& _boxHalfExtent)
{
    FCollisionShape BoxShape;
    BoxShape.SetBox(_boxHalfExtent);
    return BoxShape;
}

FCollisionShape FCollisionShape::MakeCapsule(const FVector& _extent)
{
    FCollisionShape CapsuleShape;
    CapsuleShape.SetCapsule(_extent);
    return CapsuleShape;
}

FCollisionShape FCollisionShape::MakeCapsule(const float _capsuleRadius, const float _capsuleHeight)
{
    FCollisionShape CapsuleShape;
    CapsuleShape.SetCapsule(_capsuleRadius, _capsuleHeight);
    return CapsuleShape;
}

FCollisionShape FCollisionShape::MakeSphere(const float _sphereRadius)
{
    FCollisionShape SphereShape;
    SphereShape.SetSphere(_sphereRadius);
    return SphereShape;
}
#pragma endregion

#pragma region Set
void FCollisionShape::SetBox(const FVector& _halfExtent)
{
    ShapeType = ECollisionShape::Box;
    Box.Shape->setHalfExtents(Vector3(_halfExtent.X, _halfExtent.Y, _halfExtent.Z));
}

void FCollisionShape::SetCapsule(const FVector& _extent)
{
    ShapeType = ECollisionShape::Capsule;
    Capsule.Shape->setRadius(FMath::Max(_extent.X, _extent.Z));
    Capsule.Shape->setHeight(_extent.Y * 2);
}

void FCollisionShape::SetCapsule(const float _capsuleRadius, const float _capsuleHeight)
{
    ShapeType = ECollisionShape::Capsule;
    Capsule.Shape->setRadius(_capsuleRadius);
    Capsule.Shape->setHeight(_capsuleHeight * 2);
}

void FCollisionShape::SetSphere(const float _radius)
{
    ShapeType = ECollisionShape::Sphere;
    Sphere.Shape->setRadius(_radius);
}
#pragma endregion

