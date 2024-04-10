#pragma once
#include "Widget.h"
#include "ContentField.h"
#include "SearchOutliner.h"


class Outliner : public Widget
{
	ContentField* contentField = nullptr;
	SearchOutliner* searchOutliner = nullptr;
public:
	Outliner();
	~Outliner();
public:
	void Start(class GLFWwindow* _window) override;
	void Draw() override;

};

