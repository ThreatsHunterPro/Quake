#pragma once
#include "PanelWidget.h"
#include <Source/Editor/Engine/Button.h>

enum EActorType
{
	BASIC,
	LIGHTS,
	SHAPES,
	ALL_CLASSES,

	COUNT
};

struct ClassType
{
	EActorType actorType;
};

class PlaceActorsWidget : public PanelWidget
{
	vector<Button*> filterButtons;
	vector<Button*> actorsButtons;

public:
	PlaceActorsWidget(const FString& _name, EngineWindow* _window);
	~PlaceActorsWidget();

public:
	void Draw() override;
	void Stop() override;
};