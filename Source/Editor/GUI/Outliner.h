#pragma once
#include "Widget.h"
#include "DynamicButtonField.h"

class Outliner : public Widget
{
	string expl;
	std::vector< DynamicButtonField*> field;
	CustomShader* shader = nullptr;
public:
	~Outliner();
	//Outliner(CustomShader* _shader);
public:
	void Start(GLFWwindow* _window, CustomShader* elementShader) override;
	void Start(GLFWwindow* _window) override;
	void Draw() override;
private:
	void Init(GLFWwindow* _window, CustomShader* elementShader = nullptr);
};

