#include "FRaycastCallback.h"
#include "../../../Runtime/Classes/Kismet/UKismetSystemLibrary.h"
#include "../../../Runtime/Core/Math/FVector/TVector.h"

FRaycastCallback::FRaycastCallback()
{
	hitResult = new FHitResult();
}

float FRaycastCallback::notifyRaycastHit(const RaycastInfo& _info)
{
	hitResult->position = FVector(_info.worldPoint.x, _info.worldPoint.y, _info.worldPoint.z);
	hitResult->normal = FVector(_info.worldNormal.x, _info.worldNormal.y, _info.worldNormal.z);
	hitResult->distance = _info.hitFraction;
	//hitResult->actor = _info.body;
	return float(1.0);
}
