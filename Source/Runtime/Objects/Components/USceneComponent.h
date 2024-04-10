#pragma once
#include "UComponent.h"
#include "../../Core/Math/TTransform.h"

class AActor;
class FRotator;

class USceneComponent : public UComponent
{
	FTransform transform;

public:
	USceneComponent(AActor* _owner);
	~USceneComponent() override;

	virtual void Start() override;
	virtual void Update(float _deltaTime) override;
	virtual void Stop() override;

#pragma region LocalMethods

#pragma region AddMethods

	void AddLocalTransform(const FTransform& _transform);
	void AddLocalLocation(const FVector& _location);
	void AddLocalRotation(const FQuat& _rotation);
	void AddLocalScale(const FVector& _scale);

#pragma endregion

#pragma region GetMethods

	const FTransform& GetLocalTransform() const;
	const FVector& GetLocalLocation() const;
	const FQuat& GetLocalRotation() const;
	const FVector& GetLocalScale() const;

#pragma endregion

#pragma region SetMethods

	void SetLocalTransform(const FTransform& _transform);
	void SetLocalLocation(const FVector& _location);
	void SetLocalLocationAndRotation(const FVector& _location, const FRotator& _rotation);
	void SetLocalRotation(const FQuat& _rotation);
	void SetLocalScale(const FVector& _scale);

#pragma endregion

#pragma endregion

#pragma region RelativeMethods

#pragma region AddMethods

	void AddRelativeTransform( FTransform& _location);
	void AddRelativeLocation( FVector& _location);
	void AddRelativeRotation( FQuat& _rotation);
	void AddRelativeScale( FVector& _scale);

#pragma endregion

#pragma region GetMethods

	const FTransform& GetRelativeTransform(AActor* _parent)const;
	const FVector& GetRelativeLocation(AActor* _parent)const;
	const FQuat& GetRelativeRotation(AActor* _parent)const;
	const FVector& GetRelativeScale(AActor* _parent)const;

#pragma endregion

#pragma region SetMethods

	void SetRelativeTransform( FTransform& _transform);
	void SetRelativeLocation(FVector& _location);
	void SetRelativeLocationAndRotation( FVector& _location,FRotator& _rotation);
	void SetRelativeRotation(FRotator& _rotation);
	void SetRelativeScale( FVector& _scale);

#pragma endregion

#pragma endregion
};