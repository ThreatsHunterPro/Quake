#pragma once
#include "..\..\CoreMinimal.h"

class UWorld;

class UObject
{
protected:
	UWorld* world;

public:
	UObject() = default;
	UObject(UWorld* _world);
	virtual ~UObject() = default;

public:
	void BeginDestroy();
	void FinishDestroy();
	
public:
	//template <typename T>
	//TObjectPtr<T> CreateDefaultSubobject(const FString& _name)
	//{
	//	return NewObject<T>(/*this*/);
	//}
	FORCEINLINE UWorld* GetWorld() const { return world; }
};