#include "HUD.h"
#include "Outliner.h"
#include "../../Editor/Engine/Engine.h"
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
