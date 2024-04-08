#pragma once
#include "Source/CoreMinimal.h"

class EngineWindow
{
	string title;
	vec2 size;
	vec4 bgColor;
	GLFWwindow* mainWindow;

public:
	FORCEINLINE string GetTitle() const
	{
		return title;
	}
	FORCEINLINE vec2 GetSize() const
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
