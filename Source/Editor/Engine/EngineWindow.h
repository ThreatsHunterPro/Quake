#pragma once
#include "Source/CoreMinimal.h"
#include "..\..\Runtime\Core\Math\FVector\FVector2.h"
#include "..\..\Runtime\Core\Math\FColor.h"

class EngineWindow
{
	FString title;
	FVector2 size;
	FColor bgColor;
	GLFWwindow* mainWindow;

public:
	FORCEINLINE FString GetTitle() const
	{
		return title;
	}
	FORCEINLINE FVector2 GetSize() const
	{
		return size;
	}
	FORCEINLINE GLFWwindow* GetWindow() const
	{
		return mainWindow;
	}

public:
	EngineWindow();
	~EngineWindow();

public:
	#pragma region Start

	void Start();
	void InitGLFW();

	#pragma endregion

	#pragma region Update

	void Update() const;
	void UpdateWindow() const;

	#pragma endregion

	#pragma region Stop

	void Stop() const;
	void StopWindow() const;

	#pragma endregion

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

void ResizeWindow(GLFWwindow* _window, const int _width, const int _height);
