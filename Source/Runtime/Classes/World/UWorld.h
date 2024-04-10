#pragma once
#include "../../Objects/UObject.h"
#include "reactphysics3d/reactphysics3d.h"

using namespace reactphysics3d;

class UWorld : public UObject
{
	PhysicsWorld* world = nullptr;
	PhysicsCommon physics;

public:
	UWorld();

public:
	FORCEINLINE PhysicsWorld* GetWorld()
	{
		return world;
	}
	FORCEINLINE PhysicsCommon& GetPhysics()
	{
		return physics;
	}
};