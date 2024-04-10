#include "UKismetSystemLibrary.h"
#include "../../Classes/World/UWorld.h"

bool UKismetSystemLibrary::LineTraceSingleForObjects(FVector _start, FVector _end, const TArray<AActor*>& ActorsToIgnore, FHitResult& _hitInfo)
{
	return false;
}

bool UKismetSystemLibrary::LineTraceMultiForObjects(FVector _start, FVector _end, const TArray<AActor*>& ActorsToIgnore, FHitResult& _hitInfo)
{
	Ray _ray(_start.ToReactVector3(), _end.ToReactVector3());
	//UWorld::GetWorld()->raycast(_ray,)
	return false;
}
