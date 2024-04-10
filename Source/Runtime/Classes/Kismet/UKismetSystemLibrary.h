#pragma once
#include "../../Objects/UObject.h"
#include "../../Objects/Actors/AActor.h"
#include "../../../CoreMinimal.h"
#include "../../Core/Math/FVector/TVector.h"


struct FHitResult
{
	FVector position;
	FVector normal;
	float distance;
	AActor* actor;

	bool operator!=(const FHitResult& _hitInfo)
	{
		return (actor != _hitInfo.actor && distance != _hitInfo.distance && position != _hitInfo.position && normal != _hitInfo.normal);
	}
};


class UKismetSystemLibrary : UObject
{
	static bool LineTraceSingleForObjects(FVector _start, FVector _end, const TArray<AActor* >& ActorsToIgnore, FHitResult& _hitInfo);
};