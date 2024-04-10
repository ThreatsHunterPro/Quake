#include "UKismetSystemLibrary.h"
#include "../../Classes/World/UWorld.h"
#include "../../../Editor/Engine/Engine.h"
#include "../../Classes/Raycast/FRaycastCallback.h"

bool UKismetSystemLibrary::LineTraceSingleForObjects(FVector _start, FVector _end, const TArray<AActor*>& ActorsToIgnore, FHitResult& _hitInfo)
{
	return false;
}

bool UKismetSystemLibrary::LineTraceMultiForObjects(FVector _start, FVector _end, const TArray<AActor*>& ActorsToIgnore, FHitResult& _hitInfo)
{
	FRaycastCallback _callback;
	Ray _ray(_start.ToReactVector3(), _end.ToReactVector3());
	
	Engine::GetInstance().GetWorld()->GetWorld()->raycast(_ray, &_callback);
	return false;
}
