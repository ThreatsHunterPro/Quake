#pragma once
#include "..\UObject.h"

class UStaticMeshComponent;
class USceneComponent;
class UComponent;
class FRotator;
class FMatrix;
class UWorld;

class AActor : public UObject
{
	USceneComponent* rootComponent;
	UStaticMeshComponent* staticMesh;

	FString name;
	vector<UComponent*> components;
	AActor* parent;

public:
	AActor();
	AActor(const FString& _name, UWorld* _world);
	virtual ~AActor();

	virtual void Start();
	virtual void Update(float _deltaTime);
	virtual void Stop();
public:
	FORCEINLINE const FString& GetName() const { return name; }
	FORCEINLINE UStaticMeshComponent* GetStaticMesh()const { return staticMesh; }
	FORCEINLINE void SetParent(AActor* _parent) { parent = _parent; }
	FORCEINLINE AActor* GetParent() const { return parent; }

	//World 
	const FTransform& GetActorTransform() const;
	const FVector& GetActorLocation() const;
	const FRotator& GetActorRotation() const;
	const FVector& GetActorScale() const;

	//Relative
	const FTransform& GetActorRelativeTransform() const;
	const FVector& GetActorRelativeLocation() const;
	const FRotator& GetActorRelativeRotation() const;
	const FVector& GetActorRelativeScale() const;
public:
	void InitStaticMesh(const FString& _objPath, const FString& _texturePath, const bool& _useCustomMethod);
	void AddActorLocation(const FVector& _location);
	void AddActorRotation(const float _angle, const FVector& _axis);
	void AddActorScale(const FVector& _scale);

#pragma region WORLD TRANSFORM
	// ** Transform **
	void SetActorTransform(const FVector& _location, const FRotator& _rotation, const FVector& _scale) const;
	void SetActorTransform(const FTransform& _transform) const;

	// ** Location **
	void SetActorLocation(const float _loc) const;
	void SetActorLocation(const float _locX, const float _locY, const float _locZ) const;
	void SetActorLocation(const FVector& _location) const;
	void SetActorLocationAndRotation(const FVector& _location, const FRotator& _rotation) const;

	// ** Rotation **
	void SetActorRotation(const float _rot) const;
	void SetActorRotation(const float _rotX, const float _rotY, const float _rotZ) const;
	void SetActorRotation(const FRotator& _rotation) const;

	// ** Scale **
	void SetActorScale(const float _scale) const;
	void SetActorScale(const float _scaleX, const float _scaleY, const float _scaleZ) const;
	void SetActorScale(const FVector& _scale) const;
#pragma endregion WORLD TRANSFORM

#pragma region RELATIVE TRANSFORM
	// ** Transform **
	void SetActorRelativeTransform(const FVector& _location, const FRotator& _rotation, const FVector& _scale);
	void SetActorRelativeTransform(FTransform& _transform);

	// ** Location **
	void SetActorRelativeLocation(const float _loc);
	void SetActorRelativeLocation(const float _locX, const float _locY, const float _locZ);
	void SetActorRelativeLocation(FVector& _location);

	// ** Rotation **
	void SetActorRelativeRotation(const float _rot);
	void SetActorRelativeRotation(const float _rotX, const float _rotY, const float _rotZ);
	void SetActorRelativeRotation(FRotator& _rotation);

	// ** Scale **
	void SetActorRelativeScale(const float _scale);
	void SetActorRelativeScale(const float _scaleX, const float _scaleY, const float _scaleZ);
	void SetActorRelativeScale(FVector& _scale);
#pragma endregion RELATIVE TRANSFORM

#pragma region MeshMethods
	FRotator GetActorMeshRotation() const;
	const FMatrix& GetMeshMatrix() const;
	const FVector& GetActorMeshLocation() const;
    const FVector& GetActorMeshScale() const;
	const FVector& GetActorForwardVector() const;
	const FVector& GetActorRightVector() const;
	const FVector& GetActorUpVector() const;
#pragma endregion MeshMethods

protected:
	virtual void BeginPlay();
	virtual void Update();
	virtual void Destroy();
	virtual void Tick(const float _deltaTime);
};