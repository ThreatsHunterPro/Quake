#include "URigidBody.h"
#include "../../../../Editor/Engine/Engine.h"

URigidBody::URigidBody(AActor* _owner, FVector _position, const Quaternion _rotation) : UComponent(_owner)
{
	box = Engine::GetInstance().GetUWorld()->GetPhysics().createBoxShape(_position.ToReactVector3());
	transform = new Transform(_position.ToReactVector3(), _rotation);
}

void URigidBody::Start()
{
}

void URigidBody::Update(float _deltaTime)
{

}

void URigidBody::Stop()
{
}
