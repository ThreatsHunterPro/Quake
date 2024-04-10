#pragma once
#include "..\..\CoreMinimal.h"

class UObject
{

public:
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
};