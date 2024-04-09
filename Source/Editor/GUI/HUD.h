#pragma once
#include <vector>
#include "Widget.h"
class HUD
{
protected:
	std::vector< Widget*> widgets;
public:
	HUD();
	~HUD();
public:
	void Start(GLFWwindow* _window);
	void Update();
	void End();
};

