#include "HUD.h"
#include "Outliner.h"
HUD::HUD()
{
	widgets.push_back(new Outliner());
}

HUD::~HUD()
{
	
	
	widgets.clear();
}

void HUD::Start(GLFWwindow* _window)
{
	for (Widget* _widget : widgets)
	{
		_widget->Start(_window);
	}
}

void HUD::Start(GLFWwindow* _window, CustomShader* elementShader)
{
	for (Widget* _widget : widgets)
	{
		_widget->Start(_window, elementShader);
	}
}

void HUD::Update()
{
	for (Widget* _widget : widgets)
	{
		_widget->Update();
	}
}

void HUD::End()
{
	for (Widget* _widget : widgets)
	{
		_widget->End();
	}
}
