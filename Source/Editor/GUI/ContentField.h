#pragma once
#include "Widget.h"
#include "../../CoreMinimal.h"
#include "DynamicButtonField.h"

class ContentField :Widget
{
	std::vector< DynamicButtonField*> field;

public:

public:
	void Start(class GLFWwindow* _window) override;
	void Draw(string& _expl);
public:
	void Init(class GLFWwindow* _window);
};