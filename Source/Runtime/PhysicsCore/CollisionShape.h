#pragma once
#include "../../CoreMinimal.h"
#include "../Core/Math/FMath.h"

namespace ECollisionShape
{
	enum Type
	{
		Line,
		Box,
		Sphere,
		Capsule
	};
}



struct FCollisionShape
{
	union
	{
		struct
		{
			BoxShape* Shape = nullptr;
		} Box;
		struct
		{
			CapsuleShape* Shape = nullptr;
		} Capsule;
		struct
		{
			SphereShape* Shape = nullptr;
		} Sphere;
	};

	//BoxShape* Box = nullptr;
	//float HalfExtentX;
	//float HalfExtentY;
	//float HalfExtentZ;
	//
	//CapsuleShape* Capsule = nullptr;
	//float HalfHeight;
	//
	//SphereShape* Sphere = nullptr;
	//float Radius;

	ECollisionShape::Type ShapeType;
	
public:
	FCollisionShape();
	FCollisionShape(const FCollisionShape& _copy);
public:
	static FORCEINLINE constexpr float MinBoxExtent() { return KINDA_SMALL_NUMBER; }
	static FORCEINLINE constexpr float MinCapsuleAxisHalfHeight() { return KINDA_SMALL_NUMBER; }
	static FORCEINLINE constexpr float MinCapsuleRadius() { return KINDA_SMALL_NUMBER; }
	static FORCEINLINE constexpr float MinSphereRadius() { return KINDA_SMALL_NUMBER; }

public:
	FVector GetBox() const;
	float GetCapsuleAxisHalfLength() const;
	const float GetCapsuleHalfHeight() const;
	const float GetCapsuleRadius() const;
	FVector GetExtent() const;
	const float GetSphereRadius() const;
	bool IsBox() const;
	bool IsCapsule() const;
	bool IsLine() const;
	bool IsNearlyZero() const;
	bool IsSphere() const;
	static FCollisionShape MakeBox(const FVector& _boxHalfExtent);
	static FCollisionShape MakeCapsule(const FVector& _extent);
	static FCollisionShape MakeCapsule(const float _capsuleRadius, const float _capsuleHeight);
	static FCollisionShape MakeSphere(const float _sphereRadius);
	void SetBox(const FVector& _halfExtent);
	void SetCapsule(const FVector& _extent);
	void SetCapsule(const float _capsuleRadius, const float _capsuleHeight);
	void SetSphere(const float _radius);


	static struct FCollisionShape LineShape;
};
