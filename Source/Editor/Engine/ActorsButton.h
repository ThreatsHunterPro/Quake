#pragma once
#include "Button.h"

enum EActorType
{
	BASIC,
	LIGHTS,
	SHAPES,
	ALL_CLASSES,

	COUNT
};

class ActorsButton: public Button
{
	EActorType actorType;

public:
	EActorType GetActorType() { return actorType; }

public:
	ActorsButton();
	ActorsButton(const FString& _title, const EActorType& _actorType, Action _callback = nullptr, const FString& _shortcut = "", const vector<Button*>& _button = vector<Button*>());
	~ActorsButton();
};