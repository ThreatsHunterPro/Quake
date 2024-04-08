#pragma once 
#include "..\..\CoreMinimal.h"

class TimerManager
{
	float deltaTime;
	float lastTime;

public:
	FORCEINLINE static TimerManager& GetInstance()
	{
		static TimerManager _instance;
		return _instance;
	}
	FORCEINLINE float DeltaTimeSeconds() const 
	{
		return deltaTime; 
	}

public:
	TimerManager();

public:
	void Update();
};