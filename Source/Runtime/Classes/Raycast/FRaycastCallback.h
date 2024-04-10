#pragma once
#include "reactphysics3d/reactphysics3d.h"
using namespace reactphysics3d;


class FHitResult;

class FRaycastCallback : public RaycastCallback
{
	FHitResult* hitResult = nullptr;

public:
	FRaycastCallback();
public:
	virtual float notifyRaycastHit(const RaycastInfo& _info)override;
};