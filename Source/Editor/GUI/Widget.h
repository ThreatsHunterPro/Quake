#pragma once
#include "../../CoreMinimal.h"
#include "../../Editor/Engine/Shader/CustomShader.h"


class Widget
{
protected:
	ImGuiIO* io =nullptr;
	bool isEnding = false;
public:
	Widget();
	virtual ~Widget();
public:
	FORCEINLINE bool GetIsEnding() const { return isEnding; }
public:
	virtual void Start(GLFWwindow* _window, CustomShader* elementShader);
	virtual void Start(GLFWwindow* _window);
	void Update();
	virtual void End();
	virtual void Draw();
};