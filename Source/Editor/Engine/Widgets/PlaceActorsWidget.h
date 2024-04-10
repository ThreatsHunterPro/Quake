#pragma once
#include "PanelWidget.h"
#include <Source/Editor/Engine/ActorsButton.h>


class PlaceActorsWidget : public PanelWidget
{
	vector<Button*> filterButtons;
	vector<ActorsButton*> actorsButtons;

	EActorType typeFilter;

	map<EActorType, FString> enumToString = { { BASIC, "BASIC" },
											  { LIGHTS, "LIGHTS" },
											  { SHAPES, "SHAPES" },
											  { ALL_CLASSES, "ALL CLASSES" } };

	ImGuiTextFilter search;

public:
	PlaceActorsWidget(const FString& _name, EngineWindow* _window);
	~PlaceActorsWidget();

private:
	FORCEINLINE FString EnumToString(EActorType _actorType) { return enumToString[_actorType]; }

public:
	void Draw() override;
	void Stop() override;
};