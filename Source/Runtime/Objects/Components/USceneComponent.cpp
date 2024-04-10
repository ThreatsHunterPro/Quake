#include "USceneComponent.h"
#include "../Actors/AActor.h"
#include "../../Core/Math/TTransform.h"

USceneComponent::USceneComponent(AActor* _owner) : UComponent(_owner)
{
	transform = FTransform();
}

USceneComponent::~USceneComponent()
{

}

void USceneComponent::Start()
{

}
void USceneComponent::Update(float _deltaTime)
{

}

void USceneComponent::Stop()
{

}

//ADD LOCAL

void USceneComponent::AddLocalTransform(const FTransform& _transform)
{
	transform += _transform;
}

void USceneComponent::AddLocalLocation(const FVector& _location)
{
	transform.SetLocation(transform.GetLocation() + _location);
}

void USceneComponent::AddLocalRotation(const FQuat& _rotation)
{
	transform.SetRotation(transform.GetRotation() + _rotation);
}

void USceneComponent::AddLocalScale(const FVector& _scale)
{
	transform.Scale3D += _scale;
}

const FTransform& USceneComponent::GetLocalTransform() const
{
	return transform;
}

const FVector& USceneComponent::GetLocalLocation() const
{
	return transform.GetLocation();
}

const FQuat& USceneComponent::GetLocalRotation() const
{
	return transform.GetRotation();
}

const FVector& USceneComponent::GetLocalScale() const
{
	return transform.GetScale3D();
}

// SET LOCAL

void USceneComponent::SetLocalTransform(const FTransform& _transform)
{
	transform = _transform;
}

void USceneComponent::SetLocalLocation(const FVector& _location)
{
	transform.SetLocation(_location);
}

void USceneComponent::SetLocalLocationAndRotation(const FVector& _location, const FRotator& _rotation)
{
	transform.SetLocation(_location);
	transform.SetRotation(_rotation);
}

void USceneComponent::SetLocalRotation(const FQuat& _rotation)
{
	transform.SetRotation(_rotation);
}

void USceneComponent::SetLocalScale(const FVector& _scale)
{
	transform.SetScale3D(_scale);
}

//ADD RELATIVE

void USceneComponent::AddRelativeTransform(FTransform& _transform)
{
	AActor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalTransform(_transform);
		return;
	}
	transform += _transform - GetRelativeTransform(_parent);
}

void USceneComponent::AddRelativeLocation(FVector& _location)
{
	AActor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalLocation(_location);
		return;
	}
	transform.SetLocation(_location - GetRelativeLocation(_parent));
}

void USceneComponent::AddRelativeRotation(FQuat& _rotation)
{
	AActor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalRotation(_rotation);
		return;
	}
	transform.SetRotation(_rotation - GetRelativeRotation(_parent));
}

void USceneComponent::AddRelativeScale(FVector& _scale)
{
	AActor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalScale(_scale);
		return;
	}
	transform.SetScale3D(transform.GetScale3D() + (_scale - GetRelativeScale(_parent)));
}

//GET RELATIVE
const FTransform& USceneComponent::GetRelativeTransform(AActor* _parent) const
{
	return _parent ? _parent->GetActorTransform() : GetLocalTransform();
}

const FVector& USceneComponent::GetRelativeLocation(AActor* _parent) const
{
	return _parent ? _parent->GetActorLocation() : GetLocalLocation();
}

const FQuat& USceneComponent::GetRelativeRotation(AActor* _parent) const
{
	return _parent ? GetLocalRotation()/*_parent->GetActorRotation()*/ : GetLocalRotation();
}

const FVector& USceneComponent::GetRelativeScale(AActor* _parent) const
{
	return _parent ? _parent->GetActorScale() : GetLocalScale();
}

void USceneComponent::SetRelativeTransform(FTransform& _transform)
{
	AActor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalTransform(_transform);
		return;
	}
	transform = _transform - GetRelativeTransform(_parent);
}

void USceneComponent::SetRelativeLocation(FVector& _location)
{
	AActor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalLocation(_location);
		return;
	}
	transform.SetLocation(_location - GetRelativeLocation(_parent));
}

void USceneComponent::SetRelativeLocationAndRotation(FVector& _location,FRotator& _rotation)
{
	SetRelativeLocation(_location);
	SetRelativeRotation(_rotation);
}

void USceneComponent::SetRelativeRotation(FRotator& _rotation)
{
	AActor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalRotation(_rotation);
		return;
	}
	transform.SetRotation(_rotation - GetRelativeRotation(_parent).GetRotator());
}

void USceneComponent::SetRelativeScale(FVector& _scale)
{
	AActor* _parent = GetOwner()->GetParent();
	if (!_parent)
	{
		SetLocalScale(_scale);
		return;
	}
	transform.SetScale3D(_scale - GetRelativeScale(_parent));
}

