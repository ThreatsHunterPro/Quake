#pragma once
#include "..\..\Runtime\Core\Math\FVector\FVector2.h"
#include "..\..\Runtime\Core\Math\FColor.h"
#include "Widgets/Widget.h"


class EngineWindow
{
#pragma region IMGUI
	bool my_tool_active = true;
	float my_color;
	TArray<Widget*> widgets;
#pragma endregion


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
	FORCEINLINE void AddWidget(Widget* _widget)
	{
		int _occurrences = 0;
		for (int _widgetIndex = 0; _widgetIndex < widgets.Num(); _widgetIndex++)
		{
			FString _name = _widget->GetName();
			if (_name != widgets[_widgetIndex]->GetName()) continue;
			_occurrences++;
			_widget->SetName(_name += std::to_string(_occurrences).c_str());
		}
		widgets.Add(_widget);
	}

public:
	EngineWindow();
	~EngineWindow();

public:
	#pragma region Start

	virtual void Start();
	void InitGLFW();
	void InitImGUI();

	#pragma endregion

	#pragma region Update

	void Update();
	void UpdateWidgets();
	void UpdateWindow();

	#pragma endregion

	#pragma region Stop

	void Stop();
	void StopImGUI();
	void StopWindow();

	#pragma endregion

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

void ResizeWindow(GLFWwindow* _window, const int _width, const int _height);
