#pragma once
#include "../../Objects/UObject.h"
#include "../../Objects/Actors/AActor.h"
#include "../../../CoreMinimal.h"
#include "../../Core/Math/FVector/TVector.h"


struct HitInfo
{
	FVector position;
	float distance;
	AActor* actor;

	bool operator!=(HitInfo& _hitInfo) const
	{
		//return (actor != _hitInfo.actor && distance != _hitInfo.distance && position != _hitInfo.position);
	}
};


class UKismetSystemLibrary : UObject
{



	static bool LineTraceSingleForObjects(FVector _start, FVector _end, const TArray<AActor* >& ActorsToIgnore, HitInfo& _hitInfo);

};