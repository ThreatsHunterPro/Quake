#pragma once

#include "../../CoreMinimal.h"

class Widget
{
protected:
	ImGuiIO* io =nullptr;
	bool isEnding = false;
public:
	Widget();
	virtual ~Widget();
public:
	 bool GetIsEnding() const { return isEnding; }
public:
	virtual void Start( GLFWwindow* _window);
	void Update();
	virtual void End();
	virtual void Draw();
};