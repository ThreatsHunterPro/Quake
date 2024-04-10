#pragma once
#include "../../../CoreMinimal.h"
#include "Source/Runtime/Core/Math/FRotator.h"

class AActor;

class UWorld final
{
	GLFWwindow* window;
	vector<AActor*> actors;
public:
	UWorld();
	UWorld(GLFWwindow* _window);
	~UWorld();
public:
	GLFWwindow* Window() const
	{
		return window;
	}
	void Start();
	void Update() const;
	void Stop();
public:
	void SpawnActor(const FString& _name, const FString& _mesh, const FString& _texture, bool _custom, const FTransform& _transform);
public:
	void DestroyActor(AActor* _actor);
};
