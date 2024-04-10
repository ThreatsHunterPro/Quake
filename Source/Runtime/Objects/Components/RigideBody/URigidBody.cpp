#include "URigidBody.h"
#include "../../../../Editor/Engine/Engine.h"
#include "../../Actors/AActor.h"

URigidBody::URigidBody(FVector _position, const Quaternion _rotation) : UComponent(new AActor())
{
	box = Engine::GetInstance().GetUWorld()->GetPhysics().createBoxShape(Vector3(1, 1, 1));
	transform = new Transform(_position.ToReactVector3(), _rotation);
	rigidBody = Engine::GetInstance().GetUWorld()->GetWorld()->createRigidBody(*transform);
	rigidBody->addCollider(box, *transform);
}

void URigidBody::Start()
{
}

void URigidBody::Update(float _deltaTime)
{
	Engine::GetInstance().GetUWorld()->GetWorld()->update(timeStep);
	//FVector3 _position = FVector(rigidBody->getTransform().getPosition().x, rigidBody->getTransform().getPosition().y, rigidBody->getTransform().getPosition().z);
	//actor->SetActorLocation(_position);
}

void URigidBody::Stop()
{
}
