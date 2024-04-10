#include "AActor.h"
#include "../Mesh/UStaticMeshComponent.h"
#include "../Components/USceneComponent.h"
#include "../Mesh/UPrimitiveMesh.h"
#include "../../Core/Math/Quat.h"
#include "../../Core/Math/FRotator.h"

AActor::AActor()
{
	name = "coucou";
	staticMesh = nullptr;
	//components = TArray<TObjectPtr<UActorComponent>>();
	//TObjectPtr<UActorComponent> _movement = CreateDefaultSubobject<UActorComponent>("Movement");
	/*components.Add(_movement);*/
}

AActor::AActor(const FString& _name, UWorld* _world) : UObject(_world)
{
	name = _name;
	world = _world;
	BeginPlay();
}

AActor::~AActor()
{
	components.empty();
	//delete rootComponent, staticMesh;
}

void AActor::Start()
{
	const int _componentsCount = components.size();
	for (int _index(0); _index < _componentsCount; _index++)
	{
		UComponent* _component = components[_index];
		if (!_component) return;
		_component->Start();
	}
}

void AActor::Update(float _deltaTime)
{
	const int _componentsCount = components.size();
	for (int _index(0); _index < _componentsCount; _index++)
	{
		UComponent* _component = components[_index];
		if (!_component) return;
		_component->Update(_deltaTime);
	}
}

void AActor::Stop()
{
	const int _componentsCount = components.size();
	for (int _index(0); _index < _componentsCount; _index++)
	{
		UComponent* _component = components[_index];
		if (!_component) return;
		_component->Stop();
	}
}

const FTransform& AActor::GetActorTransform() const
{
	return rootComponent->GetLocalTransform();
}

const FVector& AActor::GetActorLocation() const
{
	return rootComponent->GetLocalLocation();
}

const FRotator& AActor::GetActorRotation() const
{
	return rootComponent->GetLocalRotation().GetRotator();
}

const FVector& AActor::GetActorScale() const
{

	return rootComponent->GetLocalScale();
}

const FTransform& AActor::GetActorRelativeTransform() const
{
	return rootComponent->GetRelativeTransform(parent);
}

const FVector& AActor::GetActorRelativeLocation() const
{
	return rootComponent->GetRelativeLocation(parent);
}

const FRotator& AActor::GetActorRelativeRotation() const
{
	return rootComponent->GetRelativeRotation(parent).GetRotator();
}

const FVector& AActor::GetActorRelativeScale() const
{
	return rootComponent->GetRelativeScale(parent);
}

void AActor::BeginPlay()
{
	const int _componentsCount = components.size();
	for (int _index(0); _index < _componentsCount; _index++)
	{
		UComponent* _component = components[_index];
		if (!_component) return;
		_component->Start();
	}
}

void AActor::Tick(const float _deltaTime)
{
	Update();
}

void AActor::Update()
{
	//staticMesh->DrawElement();
}

void AActor::Destroy()
{
}

void AActor::InitStaticMesh(const FString& _objPath, const FString& _texturePath, const bool& _useCustomMethod)
{
	//staticMesh->InitCreationByType(PT_BOX);
}

void AActor::AddActorLocation(const FVector& _location)
{
	rootComponent->AddLocalLocation(_location);

	if (staticMesh)
	{
		//staticMesh->AddMeshLocation(_location);
	}
}

void AActor::AddActorRotation(const float _angle, const FVector& _axis)
{
	rootComponent->AddLocalRotation(GetActorMeshRotation());

	if (staticMesh)
	{
		staticMesh->AddMeshRotation(_angle, _axis);
	}
}

void AActor::AddActorScale(const FVector& _scale)
{
	rootComponent->AddLocalScale(_scale);

	if (staticMesh)
	{
		staticMesh->AddMeshScale(_scale);
	}
}

#pragma region WORLD TRANSFORM
void AActor::SetActorTransform(const FVector& _location, const FRotator& _rotation, const FVector& _scale) const
{
	SetActorTransform(FTransform(_rotation, _location, _scale));
}

void AActor::SetActorTransform(const FTransform& _transform) const
{
	SetActorLocation(_transform.GetLocation());
	SetActorRotation(_transform.GetRotation().GetRotator());
	SetActorScale(_transform.GetScale3D());
}

void AActor::SetActorLocation(const float _loc) const
{
	SetActorLocation(FVector(_loc));
}

void AActor::SetActorLocation(const float _locX, const float _locY, const float _locZ) const
{
	SetActorLocation(FVector(_locX, _locY, _locZ));
}

void AActor::SetActorLocation(const FVector& _location) const
{
	rootComponent->SetLocalLocation(_location);
	staticMesh->SetMeshLocation(_location);
}

void AActor::SetActorLocationAndRotation(const FVector& _location, const FRotator& _rotation) const
{
	SetActorLocation(_location);
	SetActorRotation(_rotation);
}

void AActor::SetActorRotation(const float _rot) const
{
	SetActorRotation(FRotator(_rot));
}


void AActor::SetActorRotation(const float _rotX, const float _rotY, const float _rotZ) const
{
	SetActorRotation(FRotator(_rotX, _rotY, _rotZ));
}

void AActor::SetActorRotation(const FRotator& _rotation) const
{
	rootComponent->SetLocalRotation(_rotation);
	staticMesh->SetMeshRotation(_rotation);
}

void AActor::SetActorScale(const float _scale) const
{
	SetActorScale(FVector(_scale));
}

void AActor::SetActorScale(const float _scaleX, const float _scaleY, const float _scaleZ) const
{
	SetActorScale(FVector(_scaleX, _scaleY, _scaleZ));
}

void AActor::SetActorScale(const FVector& _scale) const
{
	rootComponent->SetLocalScale(_scale);
	staticMesh->SetMeshScale(_scale);
}
#pragma endregion WORLD TRANSFORM

#pragma region RELATIVE TRANSFORM
void AActor::SetActorRelativeTransform(const FVector& _location, const FRotator& _rotation, const FVector& _scale)
{
	SetActorRelativeTransform(FTransform(_rotation, _location, _scale));
}

void AActor::SetActorRelativeTransform(FTransform& _transform)
{
	rootComponent->SetRelativeTransform(_transform);
}

void AActor::SetActorRelativeLocation(const float _loc)
{
	SetActorRelativeLocation(FVector(_loc));
}

void AActor::SetActorRelativeLocation(const float _locX, const float _locY, const float _locZ)
{
	SetActorRelativeLocation(FVector(_locX, _locY, _locZ));
}

void AActor::SetActorRelativeLocation(FVector& _location)
{
	rootComponent->SetRelativeLocation(_location);
}

void AActor::SetActorRelativeRotation(const float _rot)
{
	SetActorRelativeRotation(FRotator(_rot));
}

void AActor::SetActorRelativeRotation(const float _rotX, const float _rotY, const float _rotZ)
{
	SetActorRelativeRotation(FRotator(_rotX, _rotY, _rotZ));
}

void AActor::SetActorRelativeRotation(FRotator& _rotation)
{
	rootComponent->SetRelativeRotation(_rotation);
}

void AActor::SetActorRelativeScale(const float _scale)
{
	SetActorRelativeScale(FVector(_scale));
}

void AActor::SetActorRelativeScale(const float _scaleX, const float _scaleY, const float _scaleZ)
{
	SetActorRelativeScale(FVector(_scaleX, _scaleY, _scaleZ));
}

void AActor::SetActorRelativeScale(FVector& _scale)
{
	rootComponent->SetRelativeScale(_scale);
}

FRotator AActor::GetActorMeshRotation() const
{
	const FRotator _rot = FRotator(0.0f);
	return staticMesh ? staticMesh->GetMeshRotation() : _rot;
}

const FMatrix& AActor::GetMeshMatrix() const
{
	const FMatrix _mat = FMatrix::Identity;
	return staticMesh ? staticMesh->GetModelMatrix() : _mat;
}

const FVector& AActor::GetActorMeshLocation() const
{
	const FVector _vec = FVector(0);
	return staticMesh ? staticMesh->GetMeshPosition() : _vec;
}
const FVector& AActor::GetActorMeshScale() const
{
	const FVector _vec = FVector(0);
	return staticMesh ? staticMesh->GetMeshScale() : _vec;
}
const FVector& AActor::GetActorForwardVector() const
{
	const FVector _vec = FVector(0);
	return staticMesh ? staticMesh->GetForward() : _vec;
}
const FVector& AActor::GetActorRightVector() const
{
	const FVector _vec = FVector(0);
	return staticMesh ? staticMesh->GetRight() : _vec;
}
const FVector& AActor::GetActorUpVector() const
{
	const FVector _vec = FVector(0);
	return staticMesh ? staticMesh->GetUp() : _vec;
}
#pragma endregion RELATIVE TRANSFORM