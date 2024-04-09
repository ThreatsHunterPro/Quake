#pragma once
#include <vector>
#include "Widget.h"
#include "../../Editor/Engine/Shader/CustomShader.h"
class HUD
{
protected:
	std::vector< Widget*> widgets;
public:
	HUD();
	~HUD();
public:
	void Start(GLFWwindow* _window);
	void Start(GLFWwindow* _window, CustomShader *elementShader);
	void Update();
	void End();
};

