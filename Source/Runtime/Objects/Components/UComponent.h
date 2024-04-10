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
	virtual void Start() {}
	virtual void Update(float _deltaTime) {}
	virtual void Stop() {}
};