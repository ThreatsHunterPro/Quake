#pragma once
#include "..\..\..\CoreMinimal.h"
#include "..\UObject.h"
#include "..\Components\UActorComponent.h"

class AActor : public UObject
{
	string name;
	//TArray<TObjectPtr<UActorComponent>> components;

public:
	inline const string& GetName() const
	{
		return name;
	}

public:
	AActor();
};