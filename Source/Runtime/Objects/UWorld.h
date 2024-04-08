#pragma once
#include"Actors/AActor.h"
#include "Source/Runtime/Core/Math/FRotator.h"

class UWorld final
{
	GLFWwindow* window;
	TArray<AActor*> actors;
public:
	UWorld();
	~UWorld();
public:
	GLFWwindow* Window() const
	{
		return window;
	}
	void Start(GLFWwindow* _window);
	void Update() const;
	void Stop();
public:
	template<typename T>
	T* SpawnActor(const FString& _name, const FString& _meshPath, const FString& _texture, const FVector& _location, const FRotator& _rotator);
public:
	void DestroyActor(AActor* _actor);
};

template<typename T>
inline T* UWorld::SpawnActor(const FString& _name, const FString& _meshPath, const FString& _texture, const FVector& _location, const FRotator& _rotator)
{
	T* _actor = new T();
	AActor* _castActor = (AActor)_actor;
	if (!_castActor)
		return nullptr;
	//TODO lui mettre le transform
	return _actor;
}
