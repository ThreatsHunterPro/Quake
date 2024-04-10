#include "UWorld.h"
#include "../Actors/AActor.h"
#include "../../Managers/TimerManager.h"
#include "../../Managers/CameraManager.h"
#include "../../Managers/InputManager.h"

UWorld::UWorld()
{
	window = nullptr;
	actors = vector<AActor*>();
}

UWorld::UWorld(GLFWwindow* _window)
{
	window = _window;
	actors = vector<AActor*>();
}

UWorld::~UWorld()
{

}

void UWorld::Start()
{	
	const int _actorsCount = actors.size();
	for (int _index(0); _index < _actorsCount; _index++)
	{
		AActor* _actor = actors[_index];
		if (!_actor) return;
		_actor->Start();
	}
}

void UWorld::Update() const
{
	const int _actorsCount = actors.size();
	for (int _index(0); _index < _actorsCount; _index++)
	{
		AActor* _actor = actors[_index];
		if (!_actor) continue;
		_actor->Update(1.0f);
	}
}

void UWorld::Stop()
{
	const int _actorsCount = actors.size();
	for (int _index(0); _index < _actorsCount; _index++)
	{
		AActor* _actor = actors[_index];
		if (!_actor) return;
		_actor->Stop();
	}
}

void UWorld::SpawnActor(const FString& _name, const FString& _mesh, const FString& _texture, bool _custom, const FTransform& _transform)
{
	AActor* _actor = new AActor( _name,this);
	if (!_actor) return;

	_actor->InitStaticMesh(_mesh, _texture, _custom);
	_actor->SetActorTransform(_transform);
	actors.push_back(_actor);
}

void UWorld::DestroyActor(AActor* _actor)
{
	vector<AActor*> _new = vector<AActor*>();
	if (!_actor) return;
	for (int i = 0; i < actors.size(); i++)
	{
		if (actors[i] != _actor)
			_new.push_back(actors[i]);
	}
	actors = _new;
	_actor->BeginDestroy();
}
