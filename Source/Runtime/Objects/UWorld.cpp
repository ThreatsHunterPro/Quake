#include "UWorld.h"
#include <Source/Runtime/Core/Math/Quat.h>
#include"Source/Runtime/Managers/TimerManager.h"
#include"Source/Runtime/Managers/CameraManager.h"
#include"Source/Runtime/Managers/InputManager.h"

UWorld::UWorld()
{
	actors = TArray<AActor*>();
}

UWorld::~UWorld() = default;

void UWorld::Start(GLFWwindow* _window)
{
	window = _window;
	InputManager::GetInstance().Start(_window);

	const int _actorsCount = actors.Num();
	for (int _index = 0; _index < _actorsCount; _index++)
	{
		AActor* _actor = actors[_index];
		if (!_actor)
			return;
		//_actor->BeginPlay();
	}
}

void UWorld::Update() const
{
	TimerManager::GetInstance().Update();
	InputManager::GetInstance().Update();
	CameraManager::GetInstance().Update();
}

void UWorld::Stop()
{
	cout << "Stop World" << endl;
	//stopper les manager et les actors
}

void UWorld::DestroyActor(AActor* _actor)
{
	if (!_actor)
		return;
	actors.Remove(_actor);
}
