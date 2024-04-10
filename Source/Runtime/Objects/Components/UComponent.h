#pragma once
#include "../../../CoreMinimal.h"

class AActor;

class UComponent
{

protected:
	AActor* owner;

public:
	FORCEINLINE AActor* GetOwner() const { return owner; }

public:
	explicit UComponent(AActor* _owner) { owner = _owner; }
	virtual ~UComponent() {}

public:
	virtual void Start() = 0;
	virtual void Update(float _deltaTime) = 0;
	virtual void Stop() = 0;
};