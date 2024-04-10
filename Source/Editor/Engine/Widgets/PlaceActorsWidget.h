#pragma once
#include "PanelWidget.h"

class PlaceActorsWidget : public PanelWidget
{
public:
	PlaceActorsWidget(const FString& _name, EngineWindow* _window);
	~PlaceActorsWidget();

public:
	void Draw() override;
	void Stop() override;
};