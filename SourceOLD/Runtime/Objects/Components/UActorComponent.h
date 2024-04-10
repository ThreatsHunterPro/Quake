#pragma once
#include "..\..\..\CoreMinimal.h"

class UObject;
class AActor;

class UActorComponent
{
	//TObjectPtr<AActor> owner;

public:
	UActorComponent() = default;
	UActorComponent(UObject* _owner);
};